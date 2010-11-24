#include "Task.hpp"

using namespace std;
using namespace parport;

Task::Task(std::string const& name)
    : TaskBase(name)
{
}

Task::~Task() {
    // delete all ports
    for (PinMappings::const_iterator it = m_pin_mappings.begin(); it != m_pin_mappings.end(); ++it)
    {
	ports()->removePort(it->input->getName());
	delete it->input;
	ports()->removePort(it->output->getName());
	delete it->output;
    }
}

bool Task::watch_pin(std::string const &name, int pin) {
    // Check if there is no port named like this already
    for (PinMappings::const_iterator it = m_pin_mappings.begin(); it != m_pin_mappings.end(); ++it)
    {
        if (it->name == name)
            return false;
	if (it->pin == pin) {
	    //do we want to catch this?
	}
    }

    // Create ports for both directions
    RTT::OutputPort<parport::StateChange>* output_port =
	new RTT::OutputPort<parport::StateChange>(name);
    ports()->addPort(*output_port);
    RTT::InputPort<parport::StateChange>* input_port =
	new RTT::InputPort<parport::StateChange>("w"+name);
    ports()->addEventPort(*input_port);

    // And register the mapping
    PinMapping mapping = { name, pin, output_port, input_port};
    m_pin_mappings.push_back(mapping);

    return true;
}

bool Task::configureHook()
{
    std::auto_ptr<ParportDriver> driver(new ParportDriver());
    if ( !driver->open( _device.value(), _initial_pins.value() ) )
    {
        std::cerr << "Error opening device '" << _device.value() << "'" << std::endl;
        return false;
    }

    m_driver = driver.release();
    return true;
}

void Task::updateHook()
{
    for (PinMappings::const_iterator it = m_pin_mappings.begin(); it != m_pin_mappings.end(); ++it) {
	parport::StateChange data;

	if (it->input->readNewest(data) != RTT::NewData)
	    return;

	data.time = base::Time::now();
	if (data.rising)
	    m_driver->setDataPin(it->pin);
	else
	    m_driver->resetDataPin(it->pin);

	it->output->write(data);
    }
}

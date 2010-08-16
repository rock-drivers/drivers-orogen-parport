#include "Task.hpp"

using namespace RTT;
using namespace std;
using namespace parport;

Task::Task(std::string const& name)
    : TaskBase(name)
{
}

bool Task::configureHook()
{
    std::auto_ptr<ParportDriver> driver(new ParportDriver());
    if ( !driver->open( _device.value() ) )
    {
        std::cerr << "Error opening device '" << _device.value() << "'" << std::endl;
        return false;
    }

    m_driver = driver.release();
    return true;
}

void Task::checkPin(RTT::InputPort< parport::StateChange > &inport,
		    RTT::OutputPort< parport::StateChange > &outport,
		    unsigned int pin)
{
    if (!inport.connected())
        return;
    parport::StateChange data;
    if (!inport.read(data))
        return;

    data.time = base::Time::now();
    if (data.rising)
      m_driver->setDataPin(pin);
    else
      m_driver->resetDataPin(pin);

    outport.write(data);
}

void Task::updateHook(std::vector<RTT::PortInterface *> const& updated_ports)
{
    checkPin(_pin0,_pin0out,0);
    checkPin(_pin1,_pin1out,1);
    checkPin(_pin2,_pin2out,2);
    checkPin(_pin3,_pin3out,3);
    checkPin(_pin4,_pin4out,4);
    checkPin(_pin5,_pin5out,5);
    checkPin(_pin6,_pin6out,6);
    checkPin(_pin7,_pin7out,7);
}

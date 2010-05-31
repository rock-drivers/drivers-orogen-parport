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
    if ( !driver->open( _port.value() ) )
    {
        std::cerr << "Error opening device '" << _port.value() << "'" << std::endl;
        return false;
    }

    m_driver = driver.release();
    return true;
}

void Task::checkPin(RTT::InputPort< bool > &port,
               unsigned int pin)
{
    if (!port.connected())
        return;
    bool on;
    if (!port.read(on))
        return;

    if (on)
      m_driver->setDataPin(pin);
    else
      m_driver->resetDataPin(pin);
}

void Task::updateHook(std::vector<RTT::PortInterface *> const& updated_ports)
{
    checkPin(_pin0,0);
    checkPin(_pin1,1);
    checkPin(_pin2,2);
    checkPin(_pin3,3);
    checkPin(_pin4,4);
    checkPin(_pin5,5);
    checkPin(_pin6,6);
    checkPin(_pin7,7);
}

#include "tracker.h"

void Tracker::add_instance()
{
    m_instance_count++;
}

void Tracker::remove_instance()
{
    m_instance_count--;
}

void Tracker::add_memory(std::size_t memory)
{
    m_memory_count += memory;
}

void Tracker::remove_memory(std::size_t memory)
{
    m_memory_count -= memory;
}

std::size_t Tracker::memory() const
{
    return m_memory_count;
}

std::size_t Tracker::instances() const
{
    return m_instance_count;
}
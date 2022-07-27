#pragma once

#include <memory>
#include <mutex>
#include <condition_variable>
#include <boost/circular_buffer.hpp>
#include <boost/call_traits.hpp>

using namespace std;
using namespace boost;

template <class T>
class bounded_buffer 
{
public:
    typedef boost::circular_buffer<T> container_type;
    typedef typename container_type::size_type size_type;
    typedef typename container_type::value_type value_type;
    typedef typename boost::call_traits<value_type>::param_type param_type;

    explicit bounded_buffer(size_type capacity) 
		:m_unread(0), 
		 m_capacity(capacity),
		 m_container(capacity)
	{
	}
	~bounded_buffer()
	{
	}
    void push_front(param_type item) 
	{
		std::unique_lock<std::mutex> lk(m_mutex);
		m_not_full.wait(lk, [this] { return m_unread < m_capacity; });
        m_container.push_front(item);
        ++m_unread;
        m_not_empty.notify_one();
    }

	void pop_back(value_type* pItem) 
	{
		std::unique_lock<std::mutex> lk(m_mutex);
		m_not_empty.wait(lk, [this] { return m_unread > 0; });
		*pItem = m_container[--m_unread];
		m_container.pop_back();
		m_not_full.notify_one();
	}


    bool is_not_empty() const 
	{ 
		return m_unread > 0;
	}
    bool is_not_full() const 
	{ 
		return m_unread < m_capacity; 
	}

	bool is_empty()
	{
		return (m_unread == 0);
	}

private:
    bounded_buffer(const bounded_buffer&) = delete;              // Disabled copy constructor
    bounded_buffer& operator= (const bounded_buffer&) = delete; // Disabled assign operator

    size_type m_unread;
	size_type m_capacity;
    container_type m_container;

	mutable std::mutex m_mutex;
	std::condition_variable m_not_empty;
	std::condition_variable m_not_full;
};
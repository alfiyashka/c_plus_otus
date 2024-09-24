#ifndef CUSTOM_ALLOCATOR
#define CUSTOM_ALLOCATOR

#include <memory>

template <class T,  size_t capacity = 10>
class CustomAllocator
{
public:
    using value_type = T;
    using pointer = T*;
    CustomAllocator() noexcept : mem_pool(new value_type[capacity], std::default_delete<value_type[]>()), current_elements(0) {}
    ~CustomAllocator() noexcept { }

    template <typename U> struct rebind {
      using other = CustomAllocator<U, capacity> ;
    };

    T* allocate(std::size_t n)
    {
      if (current_elements > capacity)
      {
        throw std::bad_alloc();
      }
      pointer data = reinterpret_cast<pointer>(mem_pool.get()) + current_elements;
      current_elements++;
      return data;
    }

    void deallocate(pointer &p, std::size_t n)
    {
      current_elements -= n;
    }

    template<typename U, typename... Args>
    void construct(U* p, Args&&... args)
    {
      new (p) U(std::forward<Args>(args) ...);
    }

    template<typename U>
    void destroy(U* &p)
    {
      if (p)
      {
        (p)->~U();
      }
    }

    using propogate_on_container_copy_assigment = std::false_type;
    using propogate_on_container_move_assigment = std::false_type;
    using propogate_on_container_swap = std::false_type;
private:
    std::shared_ptr<value_type[]> mem_pool;
    int current_elements;

};


#endif
#pragma once
#include <iostream>


void* operator new[] (size_t size);


void operator delete[] (void* p) noexcept;

namespace linal {



    template<typename T>
    class Buf {

    protected:

        Buf(size_t size) :
                data_((size == 0) ? nullptr : static_cast< T* >(::operator new[](sizeof(T) * size)))
                ,size_(size) ,used_(0)
        {}

        Buf(Buf &&buf) noexcept: Buf(0) {
            swap(buf);
        }

        Buf &operator=(Buf &&buf) noexcept {
            swap(std::move(buf));
        }

        ~Buf() {
            for (int i = 0; i < used_; ++i)
                (data_ + i)->~T();

            operator delete[](data_);
        }

        void swap(Buf &buf) {
            std::swap(data_, buf.data_);
            std::swap(size_, buf.size_);
            std::swap(used_, buf.used_);
        }

        T *data_ = nullptr;
        size_t size_ = 0, used_ = 0;

        size_t GetSize() const {return size_;};
        size_t GetUsed() const {return used_;};

    public:

        Buf(const Buf& buf) = delete;
        Buf& operator=(const Buf& buf) = delete;

    };

}
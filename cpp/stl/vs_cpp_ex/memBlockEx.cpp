#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>

using namespace std;

class MemoryBlock
{
public:

   // Simple constructor that initializes the resource.
   explicit MemoryBlock(size_t length)
      : _length(length)
      , _data(new int[length])
   {
      std::cout << "In MemoryBlock(size_t). length = "
                << _length << "." << std::endl;
   }

   // Destructor.
   ~MemoryBlock()
   {
      std::cout << "In ~MemoryBlock(). length = "
                << _length << ".";

      if (_data != nullptr)
      {
         std::cout << " Deleting resource.";
         // Delete the resource.
         delete[] _data;
      }

      std::cout << std::endl;
   }

   // Copy constructor.
   MemoryBlock(const MemoryBlock& other)
      : _length(other._length)
      , _data(new int[other._length])
   {
      std::cout << "In MemoryBlock(const MemoryBlock&). length = "
                << other._length << ". Copying resource." << std::endl;

      std::copy(other._data, other._data + _length, _data);
   }

   // Copy assignment operator.
   MemoryBlock& operator=(const MemoryBlock& other)
   {
      std::cout << "In operator=(const MemoryBlock&). length = "
                << other._length << ". Copying resource." << std::endl;

      if (this != &other)
      {
         // Free the existing resource.
         delete[] _data;

         _length = other._length;
         _data = new int[_length];
         std::copy(other._data, other._data + _length, _data);
      }
      return *this;
   }

   // Retrieves the length of the data resource.
   size_t Length() const
   {
      return _length;
   }

   // Move constructor.
   MemoryBlock(MemoryBlock&& other) noexcept
    : _data(nullptr)
    , _length(0)
   {
       std::cout << "In MemoryBlock(MemoryBlock&&). length = "
             << other._length << ". Moving resource." << std::endl;

       // Copy the data pointer and its length from the
       // source object.
       _data = other._data;
       _length = other._length;
    
       // Release the data pointer from the source object so that
       // the destructor does not free the memory multiple times.
       other._data = nullptr;
       other._length = 0;
    }

   // Move assignment operator.
   MemoryBlock& operator=(MemoryBlock&& other) noexcept
   {
       std::cout << "In operator=(MemoryBlock&&). length = "
             << other._length << "." << std::endl;
       
       if (this != &other)
       {
           // Free the existing resource.
           delete[] _data;

           // Copy the data pointer and its length from the
           // source object.
           _data = other._data;
           _length = other._length;
     
           // Release the data pointer from the source object so that
           // the destructor does not free the memory multiple times.
           other._data = nullptr;
           other._length = 0;
        }

        return *this;
   }

private:
   size_t _length; // The length of the resource.
   int* _data; // The resource.
};

class MemoryBlockNew
{
 private:
   size_t _length; // The length of the resource.
   std::unique_ptr<int []> _data; // The resource.
public:
    MemoryBlockNew(size_t length)
      : _length(length)
      , _data(new int[length])
   {
   }

   ~MemoryBlockNew()
   {
   }
 
   MemoryBlockNew(const MemoryBlockNew& other) // copy constructor
   : MemoryBlockNew(other._length) 
   {
   }
    
   // A move constructor enables the resources owned by an rvalue object to be moved into an lvalue without copying
   // Move constructor moves the resources in the heap, i.e., unlike copy constructors which copy the data of the existing object and assigning it to the new object move constructor 
   // just makes the pointer of the declared object to point to the data of temporary object and nulls out the pointer of the temporary objects.
   // The move constructor is much faster than a copy constructor because it doesn't allocate memory nor does it copy memory buffers.
   MemoryBlockNew(MemoryBlockNew&& other) noexcept // move constructor
   : _data(std::exchange(other._data, nullptr)), _length(std::exchange(other._length, 0)) 
   {
   }
 
   MemoryBlockNew& operator=(const MemoryBlockNew& other) // copy assignment 
   {
     return *this = MemoryBlockNew(other);
   }

   MemoryBlockNew& operator=(MemoryBlockNew&& other) noexcept // move assignment
   {
     _length = other._length;
     std::swap(_data, other._data);
     return *this;
   }
};

int main()
{
   // Create a vector object and add a few elements to it.
   vector<MemoryBlock> vO;
   vO.push_back(MemoryBlock(25));
   vO.push_back(MemoryBlock(75));

   // Insert a new element into the second position of the vector.
   vO.insert(vO.begin() + 1, MemoryBlock(50));

   // Create a vector object and add a few elements to it.
   vector<MemoryBlockNew> v;
   v.push_back(MemoryBlockNew(25));
   v.push_back(MemoryBlockNew(75));

   // Insert a new element into the second position of the vector.
   v.insert(v.begin() + 1, MemoryBlockNew(50));
}
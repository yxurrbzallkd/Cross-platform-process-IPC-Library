# Examples

* [shmem](#shmem)
* [fmap](#file-mapping) 
* [managed shmame](#managed-shmem) - FAILS MISERABLY:
```
Scanning dependencies of target shmem_managed_test
[ 16%] Building CXX object CMakeFiles/shmem_managed_test.dir/src/shmem_managed_test.cpp.o
[ 33%] Linking CXX executable ../shmem_managed_test
/usr/bin/ld: CMakeFiles/shmem_managed_test.dir/src/shmem_managed_test.cpp.o: in function `boost::interprocess::shared_memory_object::remove(char const*)':
shmem_managed_test.cpp:(.text._ZN5boost12interprocess20shared_memory_object6removeEPKc[_ZN5boost12interprocess20shared_memory_object6removeEPKc]+0x6a): undefined reference to `shm_unlink'
/usr/bin/ld: CMakeFiles/shmem_managed_test.dir/src/shmem_managed_test.cpp.o: in function `void boost::interprocess::ipcdetail::managed_open_or_create_impl<boost::interprocess::shared_memory_object, 16ul, true, false>::priv_open_or_create<boost::interprocess::ipcdetail::create_open_func<boost::interprocess::ipcdetail::basic_managed_memory_impl<char, boost::interprocess::rbtree_best_fit<boost::interprocess::mutex_family, boost::interprocess::offset_ptr<void, long, unsigned long, 0ul>, 0ul>, boost::interprocess::iset_index, 16ul> > >(boost::interprocess::ipcdetail::create_enum_t, char const* const&, unsigned long, boost::interprocess::mode_t, void const*, boost::interprocess::permissions const&, boost::interprocess::ipcdetail::create_open_func<boost::interprocess::ipcdetail::basic_managed_memory_impl<char, boost::interprocess::rbtree_best_fit<boost::interprocess::mutex_family, boost::interprocess::offset_ptr<void, long, unsigned long, 0ul>, 0ul>, boost::interprocess::iset_index, 16ul> >)':
shmem_managed_test.cpp:(.text._ZN5boost12interprocess9ipcdetail27managed_open_or_create_implINS0_20shared_memory_objectELm16ELb1ELb0EE19priv_open_or_createINS1_16create_open_funcINS1_25basic_managed_memory_implIcNS0_15rbtree_best_fitINS0_12mutex_familyENS0_10offset_ptrIvlmLm0EEELm0EEENS0_10iset_indexELm16EEEEEEEvNS1_13create_enum_tERKPKcmNS0_6mode_tEPKvRKNS0_11permissionsET_[_ZN5boost12interprocess9ipcdetail27managed_open_or_create_implINS0_20shared_memory_objectELm16ELb1ELb0EE19priv_open_or_createINS1_16create_open_funcINS1_25basic_managed_memory_implIcNS0_15rbtree_best_fitINS0_12mutex_familyENS0_10offset_ptrIvlmLm0EEELm0EEENS0_10iset_indexELm16EEEEEEEvNS1_13create_enum_tERKPKcmNS0_6mode_tEPKvRKNS0_11permissionsET_]+0x156): undefined reference to `shm_open'
/usr/bin/ld: shmem_managed_test.cpp:(.text._ZN5boost12interprocess9ipcdetail27managed_open_or_create_implINS0_20shared_memory_objectELm16ELb1ELb0EE19priv_open_or_createINS1_16create_open_funcINS1_25basic_managed_memory_implIcNS0_15rbtree_best_fitINS0_12mutex_familyENS0_10offset_ptrIvlmLm0EEELm0EEENS0_10iset_indexELm16EEEEEEEvNS1_13create_enum_tERKPKcmNS0_6mode_tEPKvRKNS0_11permissionsET_[_ZN5boost12interprocess9ipcdetail27managed_open_or_create_implINS0_20shared_memory_objectELm16ELb1ELb0EE19priv_open_or_createINS1_16create_open_funcINS1_25basic_managed_memory_implIcNS0_15rbtree_best_fitINS0_12mutex_familyENS0_10offset_ptrIvlmLm0EEELm0EEENS0_10iset_indexELm16EEEEEEEvNS1_13create_enum_tERKPKcmNS0_6mode_tEPKvRKNS0_11permissionsET_]+0x8a2): undefined reference to `shm_open'
/usr/bin/ld: shmem_managed_test.cpp:(.text._ZN5boost12interprocess9ipcdetail27managed_open_or_create_implINS0_20shared_memory_objectELm16ELb1ELb0EE19priv_open_or_createINS1_16create_open_funcINS1_25basic_managed_memory_implIcNS0_15rbtree_best_fitINS0_12mutex_familyENS0_10offset_ptrIvlmLm0EEELm0EEENS0_10iset_indexELm16EEEEEEEvNS1_13create_enum_tERKPKcmNS0_6mode_tEPKvRKNS0_11permissionsET_[_ZN5boost12interprocess9ipcdetail27managed_open_or_create_implINS0_20shared_memory_objectELm16ELb1ELb0EE19priv_open_or_createINS1_16create_open_funcINS1_25basic_managed_memory_implIcNS0_15rbtree_best_fitINS0_12mutex_familyENS0_10offset_ptrIvlmLm0EEELm0EEENS0_10iset_indexELm16EEEEEEEvNS1_13create_enum_tERKPKcmNS0_6mode_tEPKvRKNS0_11permissionsET_]+0xa33): undefined reference to `shm_open'
/usr/bin/ld: shmem_managed_test.cpp:(.text._ZN5boost12interprocess9ipcdetail27managed_open_or_create_implINS0_20shared_memory_objectELm16ELb1ELb0EE19priv_open_or_createINS1_16create_open_funcINS1_25basic_managed_memory_implIcNS0_15rbtree_best_fitINS0_12mutex_familyENS0_10offset_ptrIvlmLm0EEELm0EEENS0_10iset_indexELm16EEEEEEEvNS1_13create_enum_tERKPKcmNS0_6mode_tEPKvRKNS0_11permissionsET_[_ZN5boost12interprocess9ipcdetail27managed_open_or_create_implINS0_20shared_memory_objectELm16ELb1ELb0EE19priv_open_or_createINS1_16create_open_funcINS1_25basic_managed_memory_implIcNS0_15rbtree_best_fitINS0_12mutex_familyENS0_10offset_ptrIvlmLm0EEELm0EEENS0_10iset_indexELm16EEEEEEEvNS1_13create_enum_tERKPKcmNS0_6mode_tEPKvRKNS0_11permissionsET_]+0xc06): undefined reference to `shm_open'
/usr/bin/ld: shmem_managed_test.cpp:(.text._ZN5boost12interprocess9ipcdetail27mET_]+0x14c9): undefined reference to `shm_open'/usr/bin/ld: CMakeFiles/shmem_managed_test.dir/src/shmem_managed_test.cpp.o:shmem_managed_test.cpp:(.text._ZN5boost12interprocess9ipcdetail27managed_open_or_create_implINS0_20shared_memory_objectELm16ELb1ELb0EE19priv_open_or_createINS1_16create_open_funcINS1_25basic_managed_memory_implIcNS0_15rbtree_best_fitINS0_12mutex_familyENS0_10offset_ptrIvlmLm0EEELm0EEENS0_10iset_indexELm16EEEEEEEvNS1_13create_enum_tERKPKcmNS0_6mode_tEPKvRKNS0_11permissionsET_[_ZN5boost12interprocess9ipcdetail27managed_open_or_create_implINS0_20shared_memory_objectELm16ELb1ELb0EE19priv_open_or_createINS1_16create_open_funcINS1_25basic_managed_memory_implIcNS0_15rbtree_best_fitINS0_12mutex_familyENS0_10offset_ptrIvlmLm0EEELm0EEENS0_10iset_indexELm16EEEEEEEvNS1_13create_enum_tERKPKcmNS0_6mode_tEPKvRKNS0_11permissionsET_]+0x1fe5): more undefined references to `shm_open' followcollect2: error: ld returned 1 exit statusmake[2]: *** [CMakeFiles/shmem_managed_test.dir/build.make:89: ../shmem_managed_test] Error 1make[1]: *** [CMakeFiles/Makefile2:80: CMakeFiles/shmem_managed_test.dir/all] Error 2
make: *** [Makefile:84: all] Error 2
```

## shmem

```c++
#include <boost/interprocess/xsi_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <cstring>
#include <cstdlib>
#include <string>

using namespace boost::interprocess;

void remove_old_shared_memory(const xsi_key &key)
{
   try{
      xsi_shared_memory xsi(open_only, key);
      xsi_shared_memory::remove(xsi.get_shmid());
   }
   catch(interprocess_exception &e){
      if(e.get_error_code() != not_found_error)
         throw;
   }
}

int main(int argc, char *argv[])
{
   if(argc == 1){  //Parent process
      //Build XSI key (ftok based)
      xsi_key key(argv[0], 1);

      remove_old_shared_memory(key);

      //Create a shared memory object.
      xsi_shared_memory shm (create_only, key, 1000);

      //Remove shared memory on destruction
      struct shm_remove
      {
         int shmid_;
         shm_remove(int shmid) : shmid_(shmid){}
         ~shm_remove(){ xsi_shared_memory::remove(shmid_); }
      } remover(shm.get_shmid());

      //Map the whole shared memory in this process
      mapped_region region(shm, read_write);

      //Write all the memory to 1
      std::memset(region.get_address(), 1, region.get_size());

      //Launch child process
      std::string s(argv[0]); s += " child ";
      if(0 != std::system(s.c_str()))
         return 1;
   }
   else{
      //Build XSI key (ftok based)
      xsi_key key(argv[0], 1);

      //Create a shared memory object.
      xsi_shared_memory shm (open_only, key);

      //Map the whole shared memory in this process
      mapped_region region(shm, read_only);

      //Check that memory was initialized to 1
      char *mem = static_cast<char*>(region.get_address());
      for(std::size_t i = 0; i < region.get_size(); ++i)
         if(*mem++ != 1)
            return 1;   //Error checking memory
   }
   return 0;
}
```

## File mapping
```c++
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstddef>
#include <cstdlib>

int main(int argc, char *argv[])
{
   using namespace boost::interprocess;

   //Define file names
   const char *FileName  = "file.bin";
   const std::size_t FileSize = 10000;

   if(argc == 1){ //Parent process executes this
      {  //Create a file
         file_mapping::remove(FileName);
         std::filebuf fbuf;
         fbuf.open(FileName, std::ios_base::in | std::ios_base::out
                              | std::ios_base::trunc | std::ios_base::binary);
         //Set the size
         fbuf.pubseekoff(FileSize-1, std::ios_base::beg);
         fbuf.sputc(0);
      }

      //Remove on exit
      struct file_remove
      {
         file_remove(const char *FileName)
            : FileName_(FileName) {}
         ~file_remove(){ file_mapping::remove(FileName_); }
         const char *FileName_;
      } remover(FileName);

      //Create a file mapping
      file_mapping m_file(FileName, read_write);

      //Map the whole file with read-write permissions in this process
      mapped_region region(m_file, read_write);

      //Get the address of the mapped region
      void * addr       = region.get_address();
      std::size_t size  = region.get_size();

      //Write all the memory to 1
      std::memset(addr, 1, size);

      //Launch child process
      std::string s(argv[0]); s += " child ";
      if(0 != std::system(s.c_str()))
         return 1;
   }
   else{  //Child process executes this
      {  //Open the file mapping and map it as read-only
         file_mapping m_file(FileName, read_only);

         mapped_region region(m_file, read_only);

         //Get the address of the mapped region
         void * addr       = region.get_address();
         std::size_t size  = region.get_size();

         //Check that memory was initialized to 1
         const char *mem = static_cast<char*>(addr);
         for(std::size_t i = 0; i < size; ++i)
            if(*mem++ != 1)
               return 1;   //Error checking memory
      }
      {  //Now test it reading the file
         std::filebuf fbuf;
         fbuf.open(FileName, std::ios_base::in | std::ios_base::binary);

         //Read it to memory
         std::vector<char> vect(FileSize, 0);
         fbuf.sgetn(&vect[0], std::streamsize(vect.size()));

         //Check that memory was initialized to 1
         const char *mem = static_cast<char*>(&vect[0]);
         for(std::size_t i = 0; i < FileSize; ++i)
            if(*mem++ != 1)
               return 1;   //Error checking memory
      }
   }

   return 0;
}
```

## managed shmem

```c++
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <string>
#include <cstdlib> //std::system

using namespace boost::interprocess;

//Define an STL compatible allocator of ints that allocates from the managed_shared_memory.
//This allocator will allow placing containers in the segment
typedef allocator<int, managed_shared_memory::segment_manager>  ShmemAllocator;

//Alias a vector that uses the previous STL-like allocator so that allocates
//its values from the segment
typedef vector<int, ShmemAllocator> MyVector;

//Main function. For parent process argc == 1, for child process argc == 2
int main(int argc, char *argv[])
{
   if(argc == 1){ //Parent process
      //Remove shared memory on construction and destruction
      struct shm_remove
      {
         shm_remove() { shared_memory_object::remove("MySharedMemory"); }
         ~shm_remove(){ shared_memory_object::remove("MySharedMemory"); }
      } remover;

      //Create a new segment with given name and size
      managed_shared_memory segment(create_only, "MySharedMemory", 65536);

      //Initialize shared memory STL-compatible allocator
      const ShmemAllocator alloc_inst (segment.get_segment_manager());

      //Construct a vector named "MyVector" in shared memory with argument alloc_inst
      MyVector *myvector = segment.construct<MyVector>("MyVector")(alloc_inst);

      for(int i = 0; i < 100; ++i)  //Insert data in the vector
         myvector->push_back(i);

      //Launch child process
      std::string s(argv[0]); s += " child ";
      if(0 != std::system(s.c_str()))
         return 1;

      //Check child has destroyed the vector
      if(segment.find<MyVector>("MyVector").first)
         return 1;
   }
   else{ //Child process
      //Open the managed segment
      managed_shared_memory segment(open_only, "MySharedMemory");

      //Find the vector using the c-string name
      MyVector *myvector = segment.find<MyVector>("MyVector").first;

      //Use vector in reverse order
      std::sort(myvector->rbegin(), myvector->rend());

      //When done, destroy the vector from the segment
      segment.destroy<MyVector>("MyVector");
   }

   return 0;
};
```


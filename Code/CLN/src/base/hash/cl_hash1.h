// Hash tables with 1 key and a value
#pragma warning (disable : 4291)

#ifndef _CL_HASH1_H
#define _CL_HASH1_H

#include "base/hash/cl_hash.h"
#include "base/cl_iterator.h"

namespace cln {

// Requirements:
// - function  bool equal (key1_type,key1_type);
// - function  unsigned long hashcode (key1_type);

template <class key1_type, class value_type> CLN_TEMPLATE
struct cl_htentry1 {
    ALLOCATE_ANYWHERE(cl_htentry1)
    key1_type key;
    value_type val;
    const value_type& htvalue () { return val; }
    cl_htentry1 (const key1_type& k, const value_type& v)
        : key (k), val (v) {}
};

template <class key1_type, class value_type> CLN_TEMPLATE
struct cl_heap_hashtable_1 : public cl_heap_hashtable <cl_htentry1 <key1_type,value_type> > {
protected:
    // Abbreviations.
    typedef cl_heap_hashtable <cl_htentry1 <key1_type,value_type> > inherited;
    typedef typename inherited::htxentry htxentry;
public:
    // Allocation.
    void* operator new (size_t size) { return malloc_hook(size); }
    // Deallocation.
    void operator delete (void* ptr) { free_hook(ptr); }
public:
    // Lookup (htref alias gethash).
    // Returns a pointer which you should immediately dereference
    // if it is not NULL.
    value_type* get (const key1_type& key)
    {
        var long index = this->_slots[hashcode(key) % this->_modulus] - 1;
        while (index >= 0) {
            if (!(index < this->_size))
                throw runtime_exception();
            if (equal(key,this->_entries[index].entry.key))
                return &this->_entries[index].entry.val;
            index = this->_entries[index].next - 1;
        }
        return NULL;
    }
    // Store (htset alias puthash).
    void put (const key1_type& key, const value_type& val)
    {
        var unsigned long hcode = hashcode(key);
        // Search whether it is already there.
        {
            var long index = this->_slots[hcode % this->_modulus] - 1;
            while (index >= 0) {
                if (!(index < this->_size))
                    throw runtime_exception();
                if (equal(key,this->_entries[index].entry.key)) {
                    this->_entries[index].entry.val = val;
                    return;
                }
                index = this->_entries[index].next - 1;
            }
        }
        // Put it into the table.
        prepare_store();
        var long hindex = hcode % this->_modulus; // _modulus may have changed!
        var long index = this->get_free_index();
        new (&this->_entries[index].entry) cl_htentry1<key1_type,value_type> (key,val);
        this->_entries[index].next = this->_slots[hindex];
        this->_slots[hindex] = 1+index;
        this->_count++;
    }
    // Remove (htrem alias remhash).
    void remove (const key1_type& key)
    {
        var long* _index = &this->_slots[hashcode(key) % this->_modulus];
        while (*_index > 0) {
            var long index = *_index - 1;
            if (!(index < this->_size))
                throw runtime_exception();
            if (equal(key,this->_entries[index].entry.key)) {
                // Remove _entries[index].entry
                *_index = this->_entries[index].next;
                this->_entries[index].~htxentry();
                // The entry is now free.
                this->put_free_index(index);
                // That's it.
                this->_count--;
                return;
            }
            _index = &this->_entries[index].next;
        }
    }
    // Iterate through the table.
    // No stuff should be inserted into the table during the iteration,
    // or you may find yourself iterating over an entry vector which has
    // already been freed!
    // ??
private:
    // Prepare a store operation: make sure that the free list is non-empty.
    // This may change the table's size!
    void prepare_store ()
    {
        if (this->_freelist < -1)
            return;
        // Can we make room?
        if (this->_garcol_fun(this))
            if (this->_freelist < -1)
                return;
        // No! Have to grow the hash table.
        grow();
    }
    void grow ()
    {
        var long new_size = this->_size + (this->_size >> 1) + 1; // _size*1.5
        var long new_modulus = inherited::compute_modulus(new_size);
        var void* new_total_vector = malloc_hook(new_modulus*sizeof(long) + new_size*sizeof(htxentry));
        var long* new_slots = (long*) ((char*)new_total_vector + 0);
        var htxentry* new_entries = (htxentry *) ((char*)new_total_vector + new_modulus*sizeof(long));
        for (var long hi = new_modulus-1; hi >= 0; hi--)
            new_slots[hi] = 0;
        var long free_list_head = -1;
        for (var long i = new_size-1; i >= 0; i--) {
            new_entries[i].next = free_list_head;
            free_list_head = -2-i;
        }
        var htxentry* old_entries = this->_entries;
        for (var long old_index = 0; old_index < this->_size; old_index++)
            if (old_entries[old_index].next >= 0) {
                var key1_type& key = old_entries[old_index].entry.key;
                var value_type& val = old_entries[old_index].entry.val;
                var long hindex = hashcode(key) % new_modulus;
                var long index = -2-free_list_head;
                free_list_head = new_entries[index].next;
                new (&new_entries[index].entry) cl_htentry1<key1_type,value_type> (key,val);
                new_entries[index].next = new_slots[hindex];
                new_slots[hindex] = 1+index;
                old_entries[old_index].~htxentry();
            }
        free_hook(this->_total_vector);
        this->_modulus = new_modulus;
        this->_size = new_size;
        this->_freelist = free_list_head;
        this->_slots = new_slots;
        this->_entries = new_entries;
        this->_total_vector = new_total_vector;
    }
};

}  // namespace cln

#endif /* _CL_HASH1_H */

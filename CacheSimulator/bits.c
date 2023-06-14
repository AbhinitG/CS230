#include "bits.h"
#include "cache.h"

int get_set(Cache *cache, address_type address) {
  // TODO:
  //  Extract the set bits from a 32-bit address.
  //
  int tag_bits = 32 - (cache->set_bits + cache->block_bits);
  unsigned int set = address;
  set <<= tag_bits;
  set >>= tag_bits;
  set >>= cache->block_bits;

  return set;
}

int get_line(Cache *cache, address_type address) {
  // TODO:
  // Extract the tag bits from a 32-bit address.
  //
  unsigned int tag = address;
  tag >>= (cache->set_bits + cache->block_bits);
  
  return tag;
}

int get_byte(Cache *cache, address_type address) {
  // TODO
  // Extract the block offset (byte index) bits from a 32-bit address.
  //
  unsigned int block = address;
  int tag_bits = 32 - (cache->block_bits + cache->set_bits);
  block <<= (tag_bits + cache->set_bits);
  block >>= (tag_bits + cache->set_bits);
  return block;
}

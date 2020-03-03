// Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).

#include <cstdio>
#include <string>
#include <iostream>
#include <stdlib.h>

#include <memory/arena.h>
#include <include/rocksdb/table.h>
#include <db/db_impl/db_impl.h>

#include "rocksdb/db.h"
#include "rocksdb/slice.h"
#include "rocksdb/options.h"
#include "rocksdb/iostats_context.h"
#include "rocksdb/perf_context.h"
#include "rocksdb/write_batch.h"

using namespace rocksdb;

std::string kDBPath = "/Users/daisy/Documents/exp";

const int KEY_NUM = 10;

int main() {

  rocksdb::SetPerfLevel(rocksdb::PerfLevel::kEnableTime);
  rocksdb::get_perf_context()->Reset();
  rocksdb::get_iostats_context()->Reset();

  DB *db;
  Options options;
  // Optimize RocksDB. This is the easiest way to get RocksDB to perform well
//  options.IncreaseParallelism();
//  options.OptimizeLevelStyleCompaction();
//  options.max_write_buffer_number = 256;
  // create the DB if it's not already present
  options.create_if_missing = true;

//  options.statistics = rocksdb::CreateDBStatistics();

//  options.env = NewNvmEnv(Env::Default());
//  options.env = NewNvmEnv(Env::Default());
//  options.write_buffer_size = 4 << 10;
//  options.arena_block_size = options.write_buffer_size + (1 << 20);

//    options.max_background_jobs = 16;

// plain table test
//  PlainTableOptions plain_table_options;
//  plain_table_options.user_key_len = 10;
//  plain_table_options.store_index_in_file = true;
//  options.table_factory.reset(
//      NewPlainTableFactory(plain_table_options));

  options.allow_mmap_writes = true;
  options.allow_mmap_reads = true;

  std::unique_ptr<SequentialFile> file;

  DestroyDB(kDBPath, options);
  // open DB
  Status s = DB::Open(options, kDBPath, &db);
  assert(s.ok());
  WriteBatch batch;
//  for (int i = 0; i < 10; ++i) {
//    batch.Put(std::to_string(i), std::string(1 << 18, 'a'));
//  }
//  for (int j = 0; j < 100; ++j) {
  for (int i = 100000000; i < 100000000 + KEY_NUM; ++i) {
//    db->Write(WriteOptions(), &batch);
    db->Put(WriteOptions(), std::to_string(i), std::to_string(i));
  }
  (reinterpret_cast<DBImpl*>(db))->TEST_FlushMemTable();
//  }

  // Put key-value
//    for (int j = 0; j < 100; j++)
//        for (int i = 0; i < KEY_NUM; ++i) {
//            s = db->Put(WriteOptions(), std::to_string(i), "value");
////        if (i > 1000 && i % 1000 == 0)
////            std::cout<<i<<std::endl;
//            assert(s.ok());
//        }

  std::string value;
//  int fail = 0;
//  // get value
  for (int i = 100000000; i < 100000000 + KEY_NUM; ++i) {
    s = db->Get(ReadOptions(), std::to_string(i), &value);
    if (value != std::to_string(i)) {
      printf("%s\n", value.c_str());
    } else {
      bool success = true;
    }
////    if (value != std::to_string(i)) {
////      fail++;
////      printf("v: %s, %s\n", std::to_string(i).c_str(), value.c_str());
////    }
////    assert(value == std::to_string(i));
  }
//  printf("fail: %d\n", fail);
//  assert(s.ok());
//  assert(value == "value");

//  std::cout << rocksdb::get_perf_context()->ToString() << std::endl;
//  std::cout << "------------STATISTICS--------------------------" << std::endl;
////  std::cout << rocksdb::get_iostats_context()->ToString() << std::endl;
//  std::cout << options.statistics->ToString() << std::endl;
//
//  std::cout << "------------STATS--------------------------" << std::endl;
//  std::string stats;
//  db->GetProperty("rocksdb.stats", &stats);
//  std::cout << std::endl << std::endl;
//  std::cout << stats << std::endl;
  delete db;
//    char* addr = static_cast<char *>(pmalloc(100));


/* CLLS index */
//
//  Arena arena(1 << 20);
//  PlainTableCllsIndexBuilder builder(&arena, 12, 8);
//  for (int i = 10000000; i < 10000100; ++i) {
//    builder.AddKeyPrefix(Slice(std::to_string(i).c_str(), 8), i - 10000000);
//  }
//  Slice index_data = builder.FillIndexes();
//  fflush(stdout);
//  printf("------------------------------------------------\n");
//  PlainTableCllsIndex index(index_data);
//
//  for (int i = 10000000; i < 10000100; ++i) {
//    uint32_t key_offset;
//    Slice key = Slice(std::to_string(i).c_str(), 8);
//    index.GetOffset(key, &key_offset);
//    std::cout << i << ": " << key_offset << std::endl;
//  }

/* Compare test */
//  auto c = BytewiseComparator();
//  std::cout << c->Compare("a", "a") << std::endl;
//  std::cout << c->Compare("a", "b") << std::endl;
//  std::cout << c->Compare("b", "a") << std::endl;
  return 0;
}

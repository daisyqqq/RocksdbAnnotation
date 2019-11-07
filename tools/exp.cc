// Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).

#include <cstdio>
#include <string>
#include <iostream>

#include "rocksdb/db.h"
#include "rocksdb/slice.h"
#include "rocksdb/options.h"
#include "rocksdb/iostats_context.h"
#include "rocksdb/perf_context.h"
#include "rocksdb/write_batch.h"
//#include "/home/daisy/Documents/Thesis/quartz/src/lib/pmalloc.h"

using namespace rocksdb;

std::string kDBPath = "/tmp/rocksdb_exp";

const int KEY_NUM = 100000;

int main() {
    rocksdb::SetPerfLevel(rocksdb::PerfLevel::kEnableTime);
    rocksdb::get_perf_context()->Reset();
    rocksdb::get_iostats_context()->Reset();

    DB *db;
    Options options;
    // Optimize RocksDB. This is the easiest way to get RocksDB to perform well
    options.IncreaseParallelism();
    options.OptimizeLevelStyleCompaction();
    options.max_write_buffer_number = 256;
    // create the DB if it's not already present
    options.create_if_missing = true;

    options.statistics = rocksdb::CreateDBStatistics();

//    options.max_background_jobs = 16;
    // open DB
    Status s = DB::Open(options, kDBPath, &db);
    assert(s.ok());
    WriteBatch batch;
    for (int i = 0; i < 1000; ++i) {
        batch.Put(std::to_string(i), "value");
    }
    for (int i = 0; i < KEY_NUM; ++i) {
        db->Write(WriteOptions(), &batch);
    }

    // Put key-value
//    for (int j = 0; j < 100; j++)
//        for (int i = 0; i < KEY_NUM; ++i) {
//            s = db->Put(WriteOptions(), std::to_string(i), "value");
////        if (i > 1000 && i % 1000 == 0)
////            std::cout<<i<<std::endl;
//            assert(s.ok());
//        }

//  std::string value;
//  // get value
//  s = db->Get(ReadOptions(), "key1", &value);
//  assert(s.ok());
//  assert(value == "value");

//  std::cout << rocksdb::get_perf_context()->ToString() << std::endl;
    std::cout << "------------STATISTICS--------------------------" << std::endl;
//  std::cout << rocksdb::get_iostats_context()->ToString() << std::endl;
    std::cout << options.statistics->ToString() << std::endl;

    std::cout << "------------STATS--------------------------" << std::endl;
    std::string stats;
    db->GetProperty("rocksdb.stats", &stats);
    std::cout << std::endl << std::endl;
    std::cout << stats << std::endl;
    delete db;
//    char* addr = static_cast<char *>(pmalloc(100));


    return 0;
}

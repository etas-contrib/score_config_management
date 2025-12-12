// *******************************************************************************
// Copyright (c) 2025 Contributors to the Eclipse Foundation
//
// See the NOTICE file(s) distributed with this work for additional
// information regarding copyright ownership.
//
// This program and the accompanying materials are made available under the
// terms of the Apache License Version 2.0 which is available at
// https://www.apache.org/licenses/LICENSE-2.0
//
// SPDX-License-Identifier: Apache-2.0
// *******************************************************************************

#include "score/config_management/config_provider/code/persistency/details/persistency_empty.h"
#include <gtest/gtest.h>

namespace score
{
namespace config_management
{
namespace config_provider
{
namespace
{

class PersistencyImplTest : public ::testing::Test
{
  protected:
    void SetUp() override
    {
        sut_ = std::make_unique<PersistencyImpl>();
    }

    std::unique_ptr<PersistencyImpl> sut_;
};

TEST_F(PersistencyImplTest, Test_ReadCachedParameterSets)
{
    RecordProperty("Priority", "3");
    RecordProperty("DerivationTechnique", "Analysis of boundary values");
    RecordProperty("TestType", "Interface test");
    RecordProperty("Verifies", "::score::platform::config_provider::PersistencyImpl::ReadCachedParameterSets()");
    RecordProperty("Description",
                   "This test verifies that ReadCachedParameterSets is called when there is no cached values.");

    ParameterMap cached_parameter_set;
    sut_->ReadCachedParameterSets(cached_parameter_set, score::cpp::pmr::get_default_resource(), nullptr);
}

TEST_F(PersistencyImplTest, Test_CacheParameterSet)
{
    RecordProperty("Priority", "3");
    RecordProperty("DerivationTechnique", "Analysis of boundary values");
    RecordProperty("TestType", "Interface test");
    RecordProperty("Verifies", "::score::platform::config_provider::PersistencyImpl::CacheParameterSet()");
    RecordProperty("Description", "This test verifies that CacheParameterSet is called with no caching performed.");

    ParameterMap cached_parameter_set;
    sut_->CacheParameterSet(cached_parameter_set, "", nullptr, false);
}

TEST_F(PersistencyImplTest, Test_SyncToStorage)
{
    RecordProperty("Priority", "3");
    RecordProperty("DerivationTechnique", "Analysis of boundary values");
    RecordProperty("TestType", "Interface test");
    RecordProperty("Verifies", "::score::platform::config_provider::PersistencyImpl::SyncToStorage()");
    RecordProperty("Description", "This test verifies that SyncToStorage is called with no caching performed.");

    sut_->SyncToStorage();
}

}  // namespace
}  // namespace config_provider
}  // namespace config_management
}  // namespace score

/**
 * @file AnimChannelAngleTest.cpp
 * @author Ricardo Paz
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <AnimChannelAngle.h>

TEST(AnimChannelAngleTest, Name){
    AnimChannelAngle channel = AnimChannelAngle();

    channel.SetName(L"Banana");

    ASSERT_EQ(channel.GetName(), L"Banana");
}


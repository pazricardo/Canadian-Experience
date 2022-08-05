/**
 * @file TimelineTest.cpp
 * @author Ricardo Paz
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <AnimChannelAngle.h>
#include <Timeline.h>

TEST(TimelineTest, Constructor)
{
    Timeline timeline;

    ASSERT_EQ(timeline.GetNumFrames(), 300);
    ASSERT_EQ(timeline.GetFrameRate(), 30);
    ASSERT_EQ(timeline.GetCurrentTime(), 0);

    timeline.SetNumFrames(200);
    timeline.SetFrameRate(25);
    timeline.SetCurrentTime(31);

    ASSERT_EQ(timeline.GetNumFrames(), 200);
    ASSERT_EQ(timeline.GetFrameRate(), 25);
    ASSERT_EQ(timeline.GetCurrentTime(), 31);
}

TEST(TimelineTest, GetDuration)
{
    Timeline timeline;

    // Default value
    ASSERT_NEAR(10, timeline.GetDuration(), 0.0001);

    // Changed duration
    timeline.SetFrameRate(375);
    ASSERT_NEAR(300.0 / 375.0, timeline.GetDuration(), 0.0001);

    timeline.SetNumFrames(789);
    ASSERT_NEAR(789.0 / 375.0, timeline.GetDuration(), 0.0001);
}

TEST(TimelineTest, GetCurrentFrame)
{
    Timeline timeline;

    // Default value
    ASSERT_EQ(0, timeline.GetCurrentFrame());

    // Changed time
    timeline.SetCurrentTime(9.27);
    ASSERT_EQ(278, timeline.GetCurrentFrame());
}

TEST(TimelineTest, Add)
{
    Timeline timeline;
    AnimChannelAngle channel;

    timeline.AddChannel(&channel);
    ASSERT_EQ(&timeline, channel.GetTimeline());
}
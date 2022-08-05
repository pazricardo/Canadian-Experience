/**
 * @file DrawableTest.cpp
 * @author Ricardo Paz
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Drawable.h>

class DrawableMock : public Drawable
{
public:
    DrawableMock(const std::wstring &name) : Drawable(name) {}

    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) override {}
    virtual bool HitTest(wxPoint pos) override { return false; }
};

TEST(DrawableTest, Constructor)
{
    DrawableMock drawable(L"Harold");
    ASSERT_EQ(std::wstring(L"Harold"), drawable.GetName());
    ASSERT_EQ(wxPoint(0,0), drawable.GetPosition());
    ASSERT_EQ(0, drawable.GetRotation());

    drawable.SetPosition(wxPoint(100,100));
    drawable.SetRotation(1.23);

    ASSERT_EQ(wxPoint(100,100), drawable.GetPosition());
    ASSERT_NEAR(1.23, drawable.GetRotation(), 0.00001);

}

TEST(DrawableTest, Association)
{
    DrawableMock body(L"Body");
    auto arm = std::make_shared<DrawableMock>(L"Arm");
    auto leg = std::make_shared<DrawableMock>(L"Leg");

    ASSERT_EQ(nullptr, arm->GetParent());
    ASSERT_EQ(nullptr, leg->GetParent());

    body.AddChild(arm);
    body.AddChild(leg);

    ASSERT_EQ(&body, arm->GetParent());
    ASSERT_EQ(&body, leg->GetParent());
}

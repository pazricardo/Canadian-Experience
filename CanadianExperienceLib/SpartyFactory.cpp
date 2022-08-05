/**
 * @file SpartyFactory.cpp
 * @author Ricardo Paz
 */

#include "pch.h"

#include <memory>

#include "SpartyFactory.h"
#include "Actor.h"
#include "Drawable.h"
#include "ImageDrawable.h"
#include "PolyDrawable.h"
#include "HeadTop.h"

using namespace std;

/**
 * This is a factory method that creates our Sparty actor.
 * @param imagesDir Directory that contains the images for this application
 * @return Pointer to an actor object.
 */
std::shared_ptr<Actor> SpartyFactory::Create(std::wstring imagesDir)
{
    shared_ptr<Actor> actor = make_shared<Actor>(L"Sparty");

    auto torso = make_shared<ImageDrawable>(L"Torso", imagesDir + L"/sparty_torso.png");
    torso->SetCenter(wxPoint(71, 207));
    torso->SetPosition(wxPoint(70, 10));
    actor->SetRoot(torso);

    auto lleg = make_shared<ImageDrawable>(L"Left Leg", imagesDir + L"/sparty_lleg.png");
    lleg->SetCenter(wxPoint(45, 25));
    lleg->SetPosition(wxPoint(-30, 0));
    torso->AddChild(lleg);

    auto rleg = make_shared<ImageDrawable>(L"Right Leg", imagesDir + L"/sparty_rleg.png");
    rleg->SetCenter(wxPoint(35, 30));
    rleg->SetPosition(wxPoint(30, 5));
    torso->AddChild(rleg);

    auto bhead = make_shared<ImageDrawable>(L"Bottom Head", imagesDir + L"/sparty_lhead.png");
    bhead->SetCenter(wxPoint(56, 37));
    bhead->SetPosition(wxPoint(0, -175));
    torso->AddChild(bhead);

    auto thead = make_shared<HeadTop>(L"Head Top", imagesDir + L"/sparty_head.png");
    thead->SetCenter(wxPoint(53, 142));
    thead->SetPosition(wxPoint(0, -31));
    bhead->AddChild(thead);

    auto larm = make_shared<ImageDrawable>(L"Left Arm", imagesDir + L"/sparty_larm.png");
    larm->SetCenter(wxPoint(21, 26));
    larm->SetPosition(wxPoint(55, -180));
    torso->AddChild(larm);

    auto rarm = make_shared<ImageDrawable>(L"Right Arm", imagesDir + L"/sparty_rarm.png");
    rarm->SetCenter(wxPoint(100, 25));
    rarm->SetPosition(wxPoint(-50, -180));
    torso->AddChild(rarm);

    auto leye = make_shared<ImageDrawable>(L"Left Eye", imagesDir + L"/sparty_reye.png");
    leye->SetCenter(wxPoint(16, 13));
    leye->SetPosition(wxPoint(-18, -27));
    thead->AddChild(leye);

    auto reye = make_shared<ImageDrawable>(L"Right Eye", imagesDir + L"/sparty_leye.png");
    reye->SetCenter(wxPoint(16, 13));
    reye->SetPosition(wxPoint(18, -27));
    thead->AddChild(reye);


    actor->AddDrawable(rleg);
    actor->AddDrawable(lleg);
    actor->AddDrawable(torso);
    actor->AddDrawable(larm);
    actor->AddDrawable(rarm);
    actor->AddDrawable(bhead);
    actor->AddDrawable(thead);
    actor->AddDrawable(leye);
    actor->AddDrawable(reye);

    return actor;
}
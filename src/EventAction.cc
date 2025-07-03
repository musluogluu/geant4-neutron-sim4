#include "EventAction.hh"

#include "G4Event.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

EventAction::EventAction()
: G4UserEventAction()
{
}

EventAction::~EventAction()
{
}

void EventAction::BeginOfEventAction(const G4Event* /*event*/)
{
}

void EventAction::EndOfEventAction(const G4Event* /*event*/)
{
}
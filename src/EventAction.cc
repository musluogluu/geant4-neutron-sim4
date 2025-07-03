#include "EventAction.hh"
#include "g4analysis.hh"

#include "G4Event.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

EventAction::EventAction()
: G4UserEventAction(),
  fAnalysisManager(G4AnalysisManager::Instance())
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
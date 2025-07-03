#include "DetectorConstruction.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction(),
  fNistManager(G4NistManager::Instance()),
  fLogicLeadCylinder(nullptr)
{
}

DetectorConstruction::~DetectorConstruction()
{
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    G4Material* worldMaterial = fNistManager->FindOrBuildMaterial("G4_AIR");
    G4Material* leadMaterial = fNistManager->FindOrBuildMaterial("G4_Pb");

    G4double worldSizeXY = 2.0 * m;
    G4double worldSizeZ  = 2.0 * m;
    G4Box* solidWorld =
        new G4Box("World",
                  0.5 * worldSizeXY,
                  0.5 * worldSizeXY,
                  0.5 * worldSizeZ);

    G4LogicalVolume* logicWorld =
        new G4LogicalVolume(solidWorld,
                            worldMaterial,
                            "World");

    G4VPhysicalVolume* physWorld =
        new G4PVPlacement(0,
                          G4ThreeVector(),
                          logicWorld,
                          "World",
                          0,
                          false,
                          0,
                          false);

    G4double cylinderRadius = 7.5 * cm;
    G4double cylinderHeight = 30.0 * cm;

    G4Tubs* solidLeadCylinder =
        new G4Tubs("LeadCylinder",
                   0.0,
                   cylinderRadius,
                   0.5 * cylinderHeight,
                   0.0 * deg,
                   360.0 * deg);

    fLogicLeadCylinder =
        new G4LogicalVolume(solidLeadCylinder,
                            leadMaterial,
                            "LeadCylinder");

    G4RotationMatrix* rotationMatrix = new G4RotationMatrix();
    rotationMatrix->rotateY(90.0 * deg);

    G4ThreeVector cylinderPosition = G4ThreeVector(0.5 * cylinderHeight, 0.0, 0.0);

    new G4PVPlacement(rotationMatrix,
                      cylinderPosition,
                      fLogicLeadCylinder,
                      "LeadCylinder",
                      logicWorld,
                      false,
                      0,
                      false);

    G4VisAttributes* leadVisAtt = new G4VisAttributes(G4Colour::Gray());
    fLogicLeadCylinder->SetVisAttributes(leadVisAtt);
    logicWorld->SetVisAttributes(G4VisAttributes::GetInvisible());

    return physWorld;
}
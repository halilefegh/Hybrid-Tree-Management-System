
#include "ArtifactManager.h"
#include <iostream>
#include <sstream>

ArtifactManager::ArtifactManager()
{
}

ArtifactManager::~ArtifactManager()
{
}

int ArtifactManager::tokenize(const std::string &line, std::string tokens[], int maxTokens) const
{
    std::istringstream iss(line);
    std::string tok;
    int count = 0;
    while (iss >> tok && count < maxTokens)
    {
        tokens[count++] = tok;
    }
    return count;
}

void ArtifactManager::parseAndExecute(const std::string &line)
{
    // TODO: read lines and execuıte each command
    // Print "Error: Unknown command" if command is not known
    std::string tokens[10];
    int count =tokenize(line,tokens,10);
    std::string command=tokens[0];
    if (command=="")
    {
        return;
    }
    
    else if (command=="ADD_ARTIFACT")
    {
        handleAddArtifact(tokens,count);
    }
    else if (command=="REMOVE_ARTIFACT")
    {
        handleRemoveArtifact(tokens,count);
    }
    else if (command=="HIRE_RESEARCHER")
    {
        handleHireResearcher(tokens,count);
    }
    else if(command=="FIRE_RESEARCHER"){
        handleFireResearcher(tokens,count);
    }
    else if(command=="REQUEST"){
        handleRequest(tokens,count);
    }
    else if (command=="RETURN")
    {
        handleReturn(tokens,count);
    }
    else if (command=="RETURN_ALL")
    {
        handleReturnAll(tokens,count);
    }
    else if(command=="RESEARCHER_LOAD"){
        handleResearcherLoad(tokens,count);
    }
    
    else if (command=="CLEAR")
    {
        handleClear(tokens,count);
    }
    else if(command=="MATCH_RARITY"){
        handleMatchRarity(tokens,count);
    }
    else if (command=="PRINT_UNASSIGNED")
    {
        
    }
    else{
        std::cout<<"Error: Unknown command"<<std::endl;
    }
    
    
    
    
    
    
    
    
}

// =================== COMMAND HANDLERS ===================

void ArtifactManager::handleAddArtifact(const std::string tokens[], int count)
{
    // Expected: ADD_ARTIFACT <id> <name> <rarity> <value>
    // TODO:
    // 1) Check parameter count.
    // 2) Convert <id>, <rarity>, <value> to integers.
    // 3) Create Artifact and attempt to insert into AVL tree.
    // 4) On success: print "Artifact <id> added."
    // 5) On duplicate: print appropriate error (as in the PDF).
    if (count<4)
    {
        std::cout<<"Error: INVALID PARAMETER"<<std::endl;
        return;
    }
    std::string name=tokens[2];
    int id,rarity,value;
    id= std::stoi(tokens[1]);
    rarity= std::stoi(tokens[3]);
    value=std::stoi(tokens[4]);
    Artifact x(id,name,rarity,value);
    bool inserted=artifactTree.insertArtifact(x);
    if(inserted){std::cout<<"Artifact "<<id<<" added."<<std::endl;}
    else{std::cout << "Error: Artifact " << id << " already exists." << std::endl;}
}

void ArtifactManager::handleRemoveArtifact(const std::string tokens[], int count)
{
    // Expected: REMOVE_ARTIFACT <id>
    // TODO:
    // 1) Parse id.
    // 2) Find artifact in AVL; if not found, print error.
    // 3) If artifact is assigned , find researcher and
    //    remove artifact from their list.
    // 4) Remove artifact from AVL; print success or error message.
    if (count<1)
    {
        return;
    }
    int id;
    id=std::stoi(tokens[1]);
    ArtifactNode* art= artifactTree.findArtifact(id);
    if (art==nullptr)
    {
        std::cout << "Error: Artifact " << id << " not found." << std::endl;
        return;
    }
    
    if (art->data.assignedToName!="")
    {
        ResearcherNode* res=researcherTree.findResearcher(art->data.assignedToName);
        if (res!=nullptr)
        {
            res->data.removeArtifact(id);
        }
        
        
    }
    artifactTree.removeArtifact(id);
    std::cout << "Artifact " << id << " removed." << std::endl;

    
}

void ArtifactManager::handleHireResearcher(const std::string tokens[], int count)
{
    // Expected: HIRE_RESEARCHER <name> <capacity>
    // TODO:
    // 1) Parse name and capacity.
    // 2) Create Researcher and insert into RedBlackTree.
    // 3) On success: "Researcher <name> hired."
    // 4) On duplicate: error message.
    if (count<2)
    {
        return;
    }
    
    std::string name=tokens[1];
    int capacity=std::stoi(tokens[2]);
    Researcher res(name,capacity);
    bool inserted=researcherTree.insertResearcher(res);
    if (inserted)
    {
        std::cout<<"Researcher "<<name<<" hired."<<std::endl;
    }
    else{
        std::cout<<"Error: Duplicate."<<std::endl;
    }
    
}

void ArtifactManager::handleFireResearcher(const std::string tokens[], int count)
{
    // Expected: FIRE_RESEARCHER <name>
    // TODO:
    // 1) Find researcher by name. If not found, print error.
    // 2) For each artifact ID in their assignment list:
    //      - clear assignedToName in AVL.
    // 3) Remove researcher from RBT.
    // 4) Print success message.
    if (count<1)
    {
        return;
    }
    
    std::string name=tokens[1];
    
    ResearcherNode* res=researcherTree.findResearcher(name);
    if (res==nullptr)
    {
        std::cout<<"Error:Researcher "<<name<<" not found."<<std::endl;
        return;
    }
    int* artifactList=res->data.assignedArtifacts;
    for (int i = 0; i < res->data.numAssigned; i++)
    {
        artifactTree.clearAssignedTo(artifactList[i]);
    }
    researcherTree.removeResearcher(name);
    std::cout<<"Researcher "<<name<<" fired."<<std::endl;
}

void ArtifactManager::handleRequest(const std::string tokens[], int count)
{
    // Expected: REQUEST <researcherName> <artifactID>
    // TODO:
    // 1) Find researcher by name; error if missing.
    // 2) Find artifact by ID; error if missing.
    // 3) Check artifact is unassigned; error if already assigned.
    // 4) Check researcher capacity; error if at full capacity.
    // 5) On success: add artifact to researcher list AND set assignedToName in AVL.
    //    Print "Artifact <id> assigned to <name>."
    if (count<2)
    {
        std::cout<<"Error:Invalid Parameters"<<std::endl;
        return;
    }
    std::string resName=tokens[1];
    int artifactID=std::stoi(tokens[2]);
    ResearcherNode* res = researcherTree.findResearcher(resName);
    if (res==nullptr)
    {
        std::cout<<"Error: Researcher "<<resName<<" not found."<<std::endl;
        return;
    }
    ArtifactNode* art=artifactTree.findArtifact(artifactID);
    if (art==nullptr)
    {
        std::cout<<"Error: Artifact "<<artifactID<<" not found."<<std::endl;
        return;
    }
    if (art->data.assignedToName!="")
    {
        std::cout<<"Error: Artifact already has a researcher."<<std::endl;
        return;
    }
    if (res->data.capacity==res->data.numAssigned)
    {
        std::cout<<"Researcher "<<resName<<" is at full capacity."<<std::endl;
        return;
    }
    res->data.addArtifact(artifactID);
    artifactTree.setAssignedTo(artifactID,resName);
    std::cout<<"Artifact "<<artifactID<<" assigned to "<<resName<<"."<<std::endl;
    
    
    

    
}

void ArtifactManager::handleReturn(const std::string tokens[], int count)
{
    // Expected: RETURN <researcherName> <artifactID>
    // TODO:
    // 1) Validate existence of researcher and artifact.
    // 2) Check that artifact.assignedToName == researcherName.
    // 3) If not, print error.
    // 4) Otherwise, remove artifact from researcher list, clear assignedToName in AVL.
    //    Print "Artifact <id> returned by <name>."
    if (count<2)
    {
        return;
    }
    std::string name=tokens[1];
    int artifactID=std::stoi(tokens[2]);
    ResearcherNode* res= researcherTree.findResearcher(name);
    if (res==nullptr)
    {
        std::cout<<"Error:Researcher "<<name<<" not found."<<std::endl;
    }
    ArtifactNode* art=artifactTree.findArtifact(artifactID);
    if (art==nullptr)
    {
        std::cout<<"Error:Artifact "<<artifactID<<" not found."<<std::endl;
        return;
    }
    if (art->data.assignedToName!=name)
    {
        std::cout<<"Error:Researcher "<<name<<" is not assigned to "<<artifactID<<"."<<std::endl;
        return;
    }
    artifactTree.clearAssignedTo(artifactID);
    res->data.removeArtifact(artifactID);
    
    
}

void ArtifactManager::handleReturnAll(const std::string tokens[], int count)
{
    // Expected: RETURN_ALL <researcherName>
    // TODO:
    // 1) Find researcher; error if missing.
    // 2) For each artifact they supervise, clear assignedToName in AVL.
    // 3) Clear researcher's assignment list (removeAllArtifacts()).
    // 4) Print appropriate confirmation message.
    if (count<1)
    {
        return;
    }
    std::string name=tokens[1];
    ResearcherNode* res=researcherTree.findResearcher(name);
    if (res==nullptr)
    {
        std::cout<<"Error:Researcher "<<name<<" not found."<<std::endl;
        return;
    }
    
    int* artifactList=res->data.assignedArtifacts;
    for (int i = 0; i < res->data.numAssigned; i++)
    {
        artifactTree.clearAssignedTo(artifactList[i]);
    }
    res->data.removeAllArtifacts();
    std::cout<<"All artifacts returned by "<<name<<"."<<std::endl;
    
}

void ArtifactManager::handleResearcherLoad(const std::string tokens[], int count)
{
    // Expected: RESEARCHER_LOAD <name>
    // TODO:
    // 1) Find researcher by name.
    // 2) If not found, print error.
    // 3) Otherwise, print number of supervised artifacts in required format.
    if (count<1)
    {
        return;
    }
    std::string name=tokens[1]; 
    
    ResearcherNode* res=researcherTree.findResearcher(name);
    if (res==nullptr)
    {
        std::cout<<"Error: Researcher "<<name<<" not found."<<std::endl;
        return;
    }
    std::cout<<res->data.numAssigned<<std::endl;
    
    
}

void ArtifactManager::handleMatchRarity(const std::string tokens[], int count)
{
    // Expected: MATCH_RARITY <minRarity>
    // TODO:
    // Traverse AVL tree and print all artifacts with rarity >= minRarity.
    // You may choose any reasonable order (probably inorder) unless specified otherwise
    // in your PDF. Artifacts may be assigned or unassigned; print as required.
    if (count<1)
    {
        return;
    }
    int minRarity=std::stoi(tokens[1]);
    artifactTree.startPrintBiggers(minRarity);

}

void ArtifactManager::handlePrintUnassigned(const std::string tokens[], int count)
{
    // Expected: PRINT_UNASSIGNED
    // TODO:
    // Print a header if needed, then call artifactTree.printUnassigned().
    artifactTree.printUnassigned();
}

void ArtifactManager::handlePrintStats(const std::string tokens[], int count)
{
    // Expected: PRINT_STATS
    // TODO:
    // 1) Compute:
    //    - totalArtifacts (artifactTree.getArtifactCount())
    //    - totalResearchers (researcherTree.getResearcherCount())
    //    - average artifact rarity (floor of totalRarity / totalArtifacts)
    //    - average researcher load (floor of totalLoad / totalResearchers)
    // 2) Print summary lines exactly as in the spec.
    // 3) Then:
    //    - Print researchers using preorder traversal:
    //      researcherTree.traversePreOrderForStats()
    //    - Print artifacts using postorder traversal:
    //      artifactTree.traversePostOrderForStats()
    //    (Exact formatting defined in your PDF.)
    int totalArtifacts=artifactTree.getArtifactCount();
    int totatlResearchhers=researcherTree.getResearcherCount();
    int averageRarity=artifactTree.getTotalRarity()/totalArtifacts;
    int researcherLoad=researcherTree.getTotalLoad()/totatlResearchhers;
    std::cout<<totalArtifacts<<std::endl;
    std::cout<<std::endl;
    std::cout<<averageRarity<<std::endl;
    std::cout<<researcherLoad<<std::endl;
    researcherTree.traversePreOrderForStats();
    artifactTree.traversePostOrderForStats();
}

void ArtifactManager::handleClear(const std::string tokens[], int count)
{
    // Expected: CLEAR
    // TODO:
    // Clear both trees and print confirmation message.
    artifactTree.clear();
    researcherTree.clear();
    // e.g. "All data cleared."
}

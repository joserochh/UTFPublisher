// Copyright 2017, Institute for Artificial Intelligence - University of Bremen
// Author: Andrei Haidu (http://haidu.eu)

#include "TFTree.h"

// Default constructor
UTFTree::UTFTree() : Root(nullptr)
{
	UE_LOG(LogTF, Warning, TEXT("[%s] Constructor of %s"),
		*FString(__FUNCTION__), *GetName());
}

// Destructor
UTFTree::~UTFTree()
{
	UE_LOG(LogTF, Warning, TEXT("[%s] Desctructor of %s"),
		*FString(__FUNCTION__), *GetName());
}

// Find Node
UTFNode* UTFTree::FindNode(const FString& InFrameId)
{
	if (Root != nullptr)
	{
		if (Root->ChildFrameId.Equals(InFrameId))
		{
			return Root;
		}
		else
		{
			TArray<UTFNode*> Stack;
			Stack.Push(Root);

			while (Stack.Num() > 0)
			{
				UTFNode* CurrNode = Stack.Pop();
				if (CurrNode->ChildFrameId.Equals(InFrameId))
				{
					return CurrNode;
				}
				for (const auto& ChildItr : CurrNode->Children)
				{
					Stack.Push(ChildItr);
				}
			}
		}
	}
	return nullptr; // Tree is empty
}

// Add tree root
bool UTFTree::AddRoot(UTFNode* InNode)
{
	if (Root == nullptr)
	{
		Root = InNode;
		return true;
	}
	return false; // Root already exists
}

// Add Node at the given frame
bool UTFTree::AddNodeAt(UTFNode* InNode, const FString& InFrameId)
{
	UTFNode* ParentNode = FindNode(InFrameId);
	if (ParentNode != nullptr)
	{
		ParentNode->Children.Emplace(InNode);
		return true;
	}
	return false; // Frame id was not found
}

// Remove only the node, connect its children to its parent
bool UTFTree::RemoveNode(UTFNode* InNode)
{
	if (InNode != nullptr)
	{
		for (auto& ChildItr : InNode->Children)
		{
			ChildItr->Parent = InNode->Parent;
		}
		return true;
	}
	return false;
}

// Remove node with its branch
bool UTFTree::RemoveBranch(UTFNode* InNode)
{
	if (InNode != nullptr)
	{
		//InNode->Children.Empty();
	}
	return false;
}

// Get all tf nodes as array
TArray<UTFNode*> UTFTree::GetNodesAsArray() const
{
	TArray<UTFNode*> NodesArray;
	if (Root != nullptr)
	{
		TArray<UTFNode*> Stack;
		Stack.Push(Root);

		while (Stack.Num() > 0)
		{
			UTFNode* CurrNode = Stack.Pop();
			NodesArray.Emplace(CurrNode);
			for (const auto& ChildItr : CurrNode->Children)
			{
				Stack.Push(ChildItr);
			}
		}
	}
	return NodesArray;
}

// String output of the tf tree
FString UTFTree::ToString() const
{
	FString TreeString;
	if (Root != nullptr)
	{
		TArray<UTFNode*> Stack;
		Stack.Push(Root);
		while (Stack.Num() > 0)
		{
			UTFNode* CurrNode = Stack.Pop();
			TreeString.Append(CurrNode->ToString());
			for (const auto& ChildItr : CurrNode->Children)
			{
				Stack.Push(ChildItr);
			}
		}
	}
	return TreeString;
}


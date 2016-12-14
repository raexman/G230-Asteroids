//
//  BucketGrid.h
//  Asteroids
//
//  Created by Rogelio Espinoza on 12/13/16.
//  Copyright © 2016 Rogelio Espinoza. All rights reserved.
//

#pragma once

#include <stdio.h>
#include <iostream>
#include "GameObject.h"

using namespace std;

class BucketGrid
{
public:
    
    static const int BUCKET_WIDTH = 100;
    static const int BUCKET_HEIGHT = 100;
    static const int COLUMNS = 10;
    static const int ROWS = 10;
    
    vector<GameObject*> objects;
    vector<GameObject*> grid[COLUMNS][ROWS];
    
    BucketGrid();
    ~BucketGrid();
    void Update(float deltaTime);
    Vector2i GetBucket(Vector2f pos);
    void Add(Vector2i b, GameObject* obj);
    void Remove(Vector2i b, GameObject* obj);
    void Collisions(GameObject* obj,Vector2i b);
    void CleanUp();
	void Push(GameObject *obj);
	void Pop(GameObject *obj);

};

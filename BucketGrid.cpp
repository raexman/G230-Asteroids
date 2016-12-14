    //
//  BucketGrid.cpp
//  Asteroids
//
//  Created by Rogelio Espinoza on 12/13/16.
//  Copyright © 2016 Rogelio Espinoza. All rights reserved.
//

#include "BucketGrid.h"

using namespace sf;

BucketGrid::BucketGrid()
{
    
}
BucketGrid::~BucketGrid()
{
	objects.clear();
	delete grid;
}

void BucketGrid::Update(float deltaTime)
{
    //std::cout << "UPDATE BUCKET" << std::endl;
    
    for(int i = 0; i < objects.size(); i++)
    {
        //Get object.
        GameObject * obj = objects[i];
        
        //Detect bucket.
        Vector2i curBucket = GetBucket(obj->getCenter());

        //Update object.
        obj->Update(deltaTime);
        
        //Detect new bucket.
        Vector2i newBucket = GetBucket(obj->getCenter());
        
        //If object changed buckets.
        if(curBucket != newBucket)
        {
            //Remove from past bucket.
            Remove(curBucket, obj);
            
            //Add to new bucket;
            Add(newBucket, obj);
        }
        
        //Check for collisions;
        Collisions(obj, newBucket);
    }
    
    CleanUp();
}

Vector2i BucketGrid::GetBucket(Vector2f pos)
{
    int col = int(pos.x / BUCKET_WIDTH);
    int row = int(pos.y / BUCKET_HEIGHT);
    
    if(col < 0)
        col = 0;
    else if(row >= COLUMNS)
        col = COLUMNS - 1;
    
    
    if(row < 0)
        row = 0;
    else if(row >= ROWS)
        row = ROWS - 1;
    
    
    return Vector2i(col, row);
}

void BucketGrid::Push(GameObject *obj)
{
	objects.push_back(obj);

	//Add(GetBucket(obj->getCenter()), obj);
}

void BucketGrid::Pop(GameObject *obj)
{
	objects.erase(remove(objects.begin(), objects.end(), obj), objects.end());

	if (obj->type == "asteroid")
	{
		buffer.loadFromFile("Assets/sounds/asteroid.wav");
		sound.setBuffer(buffer);
		sound.play();
	}
	if (obj->type == "powerup")
	{
		buffer.loadFromFile("Assets/sounds/powerup.wav");
		sound.setBuffer(buffer);
		sound.play();
	}
}

void BucketGrid::Add(Vector2i b, GameObject* obj)
{
    vector<GameObject*> &v = grid[b.x][b.y];
    v.push_back(obj);
}


void BucketGrid::Remove(Vector2i b, GameObject* obj)
{
	std::cout << "BUCKET: " << b.x << ", " << b.y << " | " << obj->type << std::endl;

    vector<GameObject*> &v = grid[b.x][b.y];

    remove(v.begin(), v.end(), obj);
}


void BucketGrid::Collisions(GameObject* obj, Vector2i b)
{
    int left = max(b.x - 1, 0);
    int right = min(b.x + 1, COLUMNS - 1);
    int top = max(b.y - 1, 0);
    int bot = min(b.y + 1, ROWS - 1);
    
    
    for(int bx = left; bx <= right; ++bx)
    {
        for(int by = top; by <= bot; ++by)
        {
            vector<GameObject*> &v = grid[bx][by];
            for(GameObject* o : v)
            {
                if(o != obj && o->isActive)
                    obj->CheckCollisionWith(o);
            }
        }
    }
}

void BucketGrid::CleanUp()
{
	/*
    for(GameObject *obj : objects)
    {
        if(!obj->isActive)
            Remove(GetBucket(obj->getCenter()), obj);
    }
	*/
}

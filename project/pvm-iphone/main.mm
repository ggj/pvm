//  Created by Danny Grein on 10/13/08.
//  Copyright TechFront Studios 2008. All rights reserved.

#import <UIKit/UIKit.h>

#include <Seed.h>
#include "app.h"

using namespace Seed;

ISceneNode *pScene;
ISceneNode *pSceneStatic;
App *pApp;

int main(int argc, char *argv[])
{ 
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	
	App app;
	pApp = &app;
	Seed::SetGameApp(pApp, argc, argv);
	
    int retVal = UIApplicationMain(argc, argv, nil, @"SeedDelegate");
    [pool release];
    return retVal;
}

//
//  ViewController.m
//  pvm-ios
//
//  Created by Thiago Moraes on 1/24/12.
//  Copyright (c) 2012 MagicTech. All rights reserved.
//

#import "ViewController.h"
#include <Seed.h>
#include "app.h"

App app;
bool bChangedView = NO;

@interface ViewController () {

}
@property (strong, nonatomic) EAGLContext *context;
@property (strong, nonatomic) GLKBaseEffect *effect;

- (void)setupGL;
- (void)tearDownGL;

@end

@implementation ViewController

@synthesize context = _context;
@synthesize effect = _effect;

- (void)dealloc
{
	[_context release];
	[_effect release];
	[super dealloc];
}

- (void)viewDidLoad
{
	[super viewDidLoad];
	
	self.context = [[[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1] autorelease];

	if (!self.context)
	{
		NSLog(@"Failed to create ES context");
	}
	
	GLKView *view = (GLKView *)self.view;
	view.context = self.context;
	view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
	
	[self setupGL];
}

- (void)viewDidUnload
{	
	[super viewDidUnload];
	
	[self tearDownGL];
	
	if ([EAGLContext currentContext] == self.context)
	{
		[EAGLContext setCurrentContext:nil];
	}
	self.context = nil;
}

- (void)didReceiveMemoryWarning
{
	[super didReceiveMemoryWarning];
	// Release any cached data, images, etc. that aren't in use.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
	// Return YES for supported orientations
	if (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown &&
		interfaceOrientation != UIInterfaceOrientationPortrait)
	{
		bChangedView = YES;
		return YES;
	}
	else
	{
		return NO;
	}
}

- (void)setupGL
{
	[EAGLContext setCurrentContext:self.context];
	
	Seed::SetGameApp(&app, 0, NULL);
	Seed::Initialize();
}

- (void)tearDownGL
{
	[EAGLContext setCurrentContext:self.context];
}

#pragma mark - GLKView and GLKViewController delegate methods

- (void)update
{
	/*
	if (bChangedView)
	{
		GLKView *view = (GLKView *)self.view;
		pScreen->Resize(view.bounds.size.width, view.bounds.size.height);
		
		pRendererDevice->Shutdown();
		pRendererDevice->Initialize();
		
		bChangedView = NO;
	}
	*/
}

- (void)Pause
{
	pSystem->Sleep();
}

- (void)Stop 
{
	Seed::Shutdown();
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
	Seed::Update();
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
	(void)event;
	NSUInteger i = 0;
	
	for (UITouch *touch in touches) 
	{
		CGPoint p = [touch locationInView:self.view];
		CGPoint tp = p;
		
		i++;
		Info("Press %d %f,%f", i, tp.x, tp.y);
		EventInputPointer ev(0, Seed::Button0, 0, 0, tp.x / pScreen->GetWidth(), tp.y / pScreen->GetHeight());
		pInput->SendEventPointerPress(&ev);
	}
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{  
	(void)event;
	NSUInteger i = 0;
	
	for (UITouch *touch in touches)
	{
		CGPoint p = [touch locationInView:self.view];
		CGPoint tp = p;
		
		iphTouchBuff[i].iTaps = [touch tapCount];
		iphTouchBuff[i].bStatus = 2;
		iphTouchBuff[i].fPosX = tp.x;
		iphTouchBuff[i].fPosY = tp.y;	
		i++;
		
		if (i == PLATFORM_MAX_INPUT)
			break;
	}
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
	(void)event;
	NSUInteger i = 0;
	
	for (UITouch *touch in touches)
	{
		CGPoint p = [touch locationInView:self.view];
		CGPoint tp = p;
		
		i++;
		//Info("Release %d %f,%f", i, tp.x, tp.y);
		EventInputPointer ev(0, Seed::Button0, 0, 1, tp.x / pScreen->GetWidth(), tp.y / pScreen->GetHeight());
		pInput->SendEventPointerRelease(&ev);
	}
}

@end

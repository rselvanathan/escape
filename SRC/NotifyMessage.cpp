/*
This class notifies messages to the player whenever an special event occurs. Such as low health
or score multiplier has been obtained/lost (This works a bit like the PlayerHUD but instead uses 
GL2DText)

Author : Romesh Selvanathan
*/

#include "NotifyMessage.h"
#include "IGameWorldListener.h"
#include "GameUtil.h"
#include "GameObject.h"
#include "GameObjectType.h"
#include "GameWorld.h"
#include "GL2DText.h"

/* Construstor */ 
NotifyMessage::NotifyMessage()
{
	mNotifyMultiplier = new GL2DText;
	mNotifyMultiplier->glSetColor(1.0, 0.7, 0, 1);
	mNotifyMultiplier->SetPosition(CVector3(270, 220, 0));

	showMulti = false;
	mTTLMulti = 100;

	mNotifyMultiLost = new GL2DText;
	mNotifyMultiLost->glSetColor(1.0, 0.7, 0, 1);
	mNotifyMultiLost->SetPosition(CVector3(270, 220, 0));

	showMultiLost = false;
	mTTLMultiLost = 100;

	mNotifyHealth = new GL2DText;
	mNotifyHealth->glSetColor(1.0, 0, 0, 1);
	mNotifyHealth->SetPosition(CVector3(310, 350, 0));
	scale = 1.0f;
	rand = 0;

	multiGained = multiLost= showLowHealth = false;

	mNotifyIntro = new GL2DText;
	mNotifyIntro->glSetColor(1.0, 1.0, 1.0, 1);
	mNotifyIntro->SetPosition(CVector3(170, 350, 0));
	showIntro = true;
	mTTLIntro = 600;

	mNotifySecondStage = new GL2DText;
	mNotifySecondStage->glSetColor(1.0, 1.0, 1.0, 1);
	mNotifySecondStage->SetPosition(CVector3(170, 350, 0));
	showStage2 = false;
	mTTLStage2 = 400;
}

/* Destructor */
NotifyMessage::~NotifyMessage()
{
	SAFE_DELETE(mNotifyMultiplier);
	SAFE_DELETE(mNotifyMultiLost);
	SAFE_DELETE(mNotifyHealth);
	SAFE_DELETE(mNotifyIntro);
	SAFE_DELETE(mNotifySecondStage);
}

/* Reset this object */
void NotifyMessage::Reset()
{
	showMulti = false;
	mTTLMulti = 100;

	showMultiLost = false;
	mTTLMultiLost = 100;

	scale = 1.0f;
	rand = 0;

	showIntro = true;
	mTTLIntro = 600;

	showStage2 = false;
	mTTLStage2 = 400;

	multiGained = multiLost= showLowHealth = false;
}

///////////////////////////////////////IGAMEWORLD/////////////////////////////////////////////////

void NotifyMessage::OnObjectRemoved(GameWorld* world, GameObject* object)
{
	// if coin has been picked up push back a score message into the score list
	if(object->GetType() == GameObjectType("coin")){
		GL2DText* gl = new GL2DText;
		gl->glSetColor(1, 1, 0, 1);
		gl->SetPosition(CVector3(320, 300, 0));
		mScores.push_back(gl);
	}

	// if enemy has been killed up push back a score message into the score list
	// also alow the message to multiplier obtained to show up
	if(object->GetType() == GameObjectType("enemy")){
		GL2DText* gl = new GL2DText;
		gl->glSetColor(1, 1, 0, 1);
		gl->SetPosition(CVector3(300, 300, 0));
		mScores.push_back(gl);
		
		showMulti = true;
		// tell notifier that a multiplier has just been gained so you can show the message again
		// after the multiplier has been lost 
		multiLost = false;
	}
}

/////////////////////////////////////IENEMYLISTENER///////////////////////////////////////////////

void NotifyMessage::OnEnemyAttack()
{
	showMultiLost = true;
	// tell notifier that a multiplier has just been lost so you can show the message again
	// after the multiplier has been gained
	multiGained = false;
}

///////////////////////////////////IPLAYERLISTENER/////////////////////////////////////////////////

void NotifyMessage::OnHealthChanged(int health)
{
	// if health is below a certain value show the low health message
	if(health < 30)
		showLowHealth = true;
	else showLowHealth = false;
}

////////////////////////////////////Portal////////////////////////////////////////////////////////
void NotifyMessage::OnPortalEnter(int portal)
{
	// if the first portal has been entered then show the help for the seond part of the world
	if(portal == 1)
		showStage2 = true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////

/* Update this object */ 
void NotifyMessage::Update(float dt)
{
	// if the list of score texts is greater than 0
	if(mScores.size() > 0) {
		for(ScoreList::iterator it = mScores.begin(); it != mScores.end(); it++)
		{
			// update the position of the text by continously making it float upwards
			CVector3 m = (*it)->GetPosition();
			m.y += 100 * dt;
			(*it) ->SetPosition(m);

			// when the text reaches a height remove it from the list
			if((*it)->GetPosition().y > 400){
				mScores.remove((*it));
				// make sure to come out of the loop so if only one object exists in the list 
				// and it is removed this makes sure that it checks the if statement without causing
				// a error where for loop cannot go on due to the list actually being empty
				return;
			}
		}
	}

	// if multiplier gained messgage is being shown
	if(showMulti){
		// decrease value
		mTTLMulti -= 100 * dt;
		if(mTTLMulti <= 0){
			// do not show the message
			showMulti = false;
			mTTLMulti = 100;
			// tell notfier that thsi message has been shown already
			multiGained = true;
		}
	}

	// if multiplier lost messgage is being shown
	if(showMultiLost){
		// decrease value
		mTTLMultiLost -= 100 * dt;
		if(mTTLMultiLost <= 0){
			// do not show the message
			showMultiLost = false;
			mTTLMultiLost = 100;
			// tell notfier that thsi message has been shown already
			multiLost = true;
		}
	}

	// if low health messgage is being shown
	if(showLowHealth){
		// Causes the text to pulsate
		scale = 1 - 0.1 * (float(cos(rand)));
		rand += 10 * dt;
		mNotifyHealth->SetScale(scale);
	}

	// if intro messgage is being shown
	if(showIntro){
		// decrease value
		mTTLIntro -= 100 * dt;
		if(mTTLIntro <= 0){
			// do not show the message
			showIntro = false;
			mTTLIntro = 400;
		}
	}

	// if stage 2 messgage is being shown
	if(showStage2){
		// decrease value
		mTTLStage2 -= 100 * dt;
		if(mTTLStage2 <= 0){
			// do not show the message
			showStage2 = false;
			mTTLStage2 = 400;
		}
	}

}

/* Render this object onto the scren */
void NotifyMessage::Render()
{
	// if the list of score texts is greater than 0
	if(mScores.size() > 0) {
		for(ScoreList::iterator it = mScores.begin(); it != mScores.end(); it++)
		{
			// render the text
			(*it)->glPrint(" + score ", GL2DText::NORMAL);
		}
	}
	
	// if multiplier shown is true, and multiplier lost is false as well as being the first time
	// since last multiplier loss then show this message
	if(showMulti && !showMultiLost && !multiGained) {
		mNotifyMultiplier->glPrint(" x2 Multiplier " , GL2DText::ITALIC);
	}

	// if multiplier shown is true and it is the first time since last multiplier gain then show this message
	if(showMultiLost && !multiLost)
		mNotifyMultiLost ->glPrint(" Multiplier Lost ", GL2DText::ITALIC);

	if(showLowHealth)
		mNotifyHealth->glPrint(" LOW HEALTH ", GL2DText::ITALIC);

	if(showIntro)
		mNotifyIntro->glPrint(" Move boxes to their colored switches", GL2DText::ITALIC);

	if(showStage2)
		mNotifySecondStage->glPrint(" Do the Same , but with 3 boxes now ", GL2DText::ITALIC);
}
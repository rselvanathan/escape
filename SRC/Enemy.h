/*
The Enemy has 4 states which are to chase the player, to wander around if nothing is in sight, to attack the player from a ranged position and
to attack the player when the player attacks the enemy without the enemy attacking first. I have included some fuzzy logic in the enemy, where depending on the
current health of the enemy, it will either be agreesive towards the player or less aggressive. Enemy turns very aggressive when he has low health left and
will chase the player down no matter what happens and shoot aswell. At the same time its speed will increase aswel. When the enemy is at half health the enemy will not
attack the player from ranged instead will chase him ONLY if the player is in the enemy sight. If the enemy is unharmed he will behave normally and not be as aggressive.

Author : Romesh Selvanathan

References : http://en.csharp-online.net/XNA_Game_Programming%E2%80%94Enemy
*/ 
#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "GameUtil.h"
#include "GameObject.h"
#include "CRandom.h"
#include "CollisionManager.h"
#include "IEnemyListener.h"

//////////////////////////////////////////WANDERING///////////////////////////////////////////////////////////////////////////////////////////////
#define WANDER_MAX_MOVES 3				// Number of moves before it returns back to start position
#define WANDER_DISTANCE 30.0f			// Minimum Wandering Distance per each movemen
#define MOVE_CONSTANT 20.0f				// The Speed the enemy moves by 
#define EPSILON_DISTANCE 10.f			// A epsilon value to see if distance is below it ( SO that the enemy can generate a new wander distance) 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////ATTACKING///////////////////////////////////////////////////////////////////////////////////////////////
#define PERCEPT_DISTANCE 180.f			// Distance where enemy will start chasing the player from center of enemy
#define SHOOT_PERCEPT_DISTANCE 250.f	// Distance where enemy will start attacking player from ranged
#define SHOOT_DELAY 150					// A Delay before the next shoot method is called
#define ATTACK_DELAY 100				// A delay before the next melee attack is allowed
#define ATTACKED_CHASE_DELAY 200		// A Timer value that determines how long the enemy should chase the player when attacked
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define HEALTH_POINTS 3					// The Health of the enemy
#define UPDATE_HEALTH_DELAY 60			// A Delay to decrease the health value. Used because when the shoot object goes through the collision sphere
										// of the enemy the updates occur to frequently so had to put this up making the health go down by one at a time

class Enemy : public GameObject 
{
public:
	/* Construstor */ 
	Enemy();
	/* Destructor */
	virtual ~Enemy();

	///////////////////////////////////////GameObject Inherited methods/////////////////////////////////
	virtual void Update(float dt);
	virtual bool CollisionTest(Entity* o);
	virtual void OnCollision(Entity* o);
	////////////////////////////////////////////////////////////////////////////////////////////////////

	/* Update the Enemy according to its current health */ 
	void UpdateEnemy();
	/* Update the current state of the enemy ( Includes some fuzzy logic ) */ 
	void UpdateEnemyState(float chase, float dt);
	/* Shoot A bullet */ 
	void ShootBullet(CVector3 direction);
	/* Attack the Player from ranged position  */
	void Attack();
	/* Wander In a random Direction */ 
	void Wander();
	/* Chase the player */ 
	void Chase(float dt);
	/* Move in a Direction */ 
	void Move(CVector3 direction);
	/* Obtain a Random wandering vector */ 
	CVector3 RandomPosition();
	/*States of the Enemy	*/ 
	enum{WANDER, ATTACK, CHASE, ATTACKED};

	/* Set the Player position in order to chase and attack */ 
	void SetPlayerPosition(const CVector3 mPosition) {mPlayerPosition = mPosition;}
	/* Set the wandering start position so that the enemy always returns to this position */ 
	void SetWanderStartPositon(const CVector3 mPosition){wanderStartPosition = mPosition;
							wanderDestPosition = wanderStartPosition;}

	/* Add Listeners */ 
	void AddListener(SmartPtr<IEnemyListener> lptr){mListeners.push_back(lptr);}
	/*  Fire message to all listeners */ 
	void FireEnemyAttack(){
		for(ListenerList::iterator it = mListeners.begin(); it != mListeners.end(); it++)
			(*it)->OnEnemyAttack();
	}

private:
	CVector3 mChaseVector;				// The Vector to follow to chase the Player
	CVector3 mPlayerPosition;			// The current position of the player

	int mState;							// Current state of the Enemy
	int mHealth;						// Current Health of the enemy
	float m_r, m_g, m_b;				// Color of the enemy model
	
	int wanderMovesCount;				// number of moves covered 
	CVector3 wanderStartPosition;		// the wandering start position
	CVector3 wanderDestPosition;		// the wandering end position

	CVector3 mForward;					// the forward Vector of the enemy
	float turnAngle;					// the amount turned by the enemy	
	float speedMultiplier;				// the speed multiplier 

	CRandom r;							// Custom random generator class

	bool m_hasShot;						// A boolean to see if enemy has shot recently
	int m_tillNextShot;					// time till next shot is allowed

	bool m_hasAttacked;					// A boolean to see if enemy has melee attacked recently
	int m_tillNextAttack;				// time till next attack is allowed

	bool m_hasBeenAttacked;				// A boolean to see it enemy has been attacked by the player recently
	int m_tillNextUpdate;				// time till next update is allowed
		
	bool m_attackChase;					// A boolean to see if enemy has chased the player completly yet
	int m_tillNextChase;				// time allowed till the enemy stops chasing the player

	typedef list<SmartPtr<IEnemyListener>> ListenerList;
	ListenerList mListeners;			// List of listeners to this enemy
			
	SmartPtr<Model_3DS> enemyModel;		// Tje 3DS model for the enemy
};

#endif 
/*
The Enemy has 4 states which are to chase the player, to wander around if nothing is in sight, to attack the player from a ranged position and
to attack the player when the player attacks the enemy without the enemy attacking first. I have included some fuzzy logic in the enemy, where depending on the
current health of the enemy, it will either be agreesive towards the player or less aggressive. Enemy turns very aggressive when he has low health left and
will chase the player down no matter what happens and shoot aswell. At the same time its speed will increase aswel. When the enemy is at half health the enemy will not
attack the player from ranged instead will chase him ONLY if the player is in the enemy sight. If the enemy is unharmed he will behave normally and not be as aggressive.

Author : Romesh Selvanathan

References : http://en.csharp-online.net/XNA_Game_Programming%E2%80%94Enemy
			 http://quakewiki.net/archives/aicafe/tutorial/fuzzy.htm
*/ 
#include "Enemy.h"
#include "GameObject.h"
#include "GameUtil.h"
#include "PreLoader.h"
#include "CRandom.h"
#include "BoundingSphere.h"
#include "GameWorld.h"
#include "Shoot.h"
#include "Model_3DS.h"
#include "ExplosionFireParticle.h"
#include "ExplosionSmokeParticle.h"
#include "ExplosionParticle.h"


/* Constructor */ 
Enemy::Enemy() : GameObject("enemy", NULL),//PreLoader::GetInstance()->enemyModel),
				 mChaseVector(CVector3(0, 0, 0)),
				 mPlayerPosition(CVector3(0, 0, 0)),
				 mForward(CVector3(0, 0, 1)),
				 mState(WANDER),
				 wanderMovesCount(0),
				 wanderStartPosition(mPosition),
				 wanderDestPosition(wanderStartPosition),
				 turnAngle(0),
				 m_hasShot(false),
				 m_tillNextShot(SHOOT_DELAY),
				 m_hasAttacked(false),
				 m_tillNextAttack(ATTACK_DELAY),
				 m_hasBeenAttacked(false),
				 m_tillNextUpdate(UPDATE_HEALTH_DELAY),
				 m_attackChase(false),
				 m_tillNextChase(ATTACKED_CHASE_DELAY),
				 mHealth(HEALTH_POINTS),
				 m_r(1), m_b(1), m_g(1),
				 speedMultiplier(1)
{
	// Set the Bounding Sphere up
	mBoundingSphere = new BoundingSphere(this, 20);

	// Load the enemy model
	enemyModel = new Model_3DS();
	enemyModel->Load("Slim2.3ds");
	SetModel(enemyModel);

	mGroundValue = 27;
}

/* Destructor */ 
Enemy::~Enemy()
{
	GameObject::~GameObject();
}

/* Update the Enemy */ 
void Enemy::Update(float dt)
{
	// Obtain the Chase Vector by taking away current player position by the 
	// Enemy position
	mChaseVector = mPlayerPosition - mPosition;
	// Obtain the magnitude of the ChaseVector
	float chaseDistance = mChaseVector.Length();
	
	// Update the current state of the enemy ( Includes some fuzzy logic ) 
	UpdateEnemyState(chaseDistance, dt);

	// Switch between the States
	switch (mState)
	{
		case ATTACK : Attack(); break;
		case WANDER : Wander(); break;
		case CHASE : Chase(dt); break;
		case ATTACKED : Chase(dt); break;
	}  

	// if the angle of rotation is greater the current rotation
	if(mYRot < turnAngle)
		// add rotation
		// NOTE : 100 seems to be the right amount to make turn fast enough for when the direction changes again
		mYRot += 100.f * dt;
	// if the angle of rotation is less than the current rotation
	else if (mYRot > turnAngle)
		// subtract the rotation
		mYRot -= 100.f * dt;

	// Update the Game Object
	GameObject::Update(dt);

	// if enemy has shot
	if(m_hasShot){
		// decrease value
		m_tillNextShot -= 100 * dt;
		// check to make sure it don't go below 0
		if(m_tillNextShot < 0) {m_tillNextShot = 0;}
		// if 0 reset the value and allow shooting again
		if(m_tillNextShot==0){
			m_hasShot = false;
			m_tillNextShot = SHOOT_DELAY;
		}
	}

	// if enemy has attacked 
	if(m_hasAttacked){
		// decrease value
		m_tillNextAttack -= 100 * dt;
		// check to make sure it don't go below 0
		if(m_tillNextAttack < 0) {m_tillNextAttack = 0;}
		// if 0 reset the value and allow attacking again
		if(m_tillNextAttack==0){
			m_hasAttacked = false;
			m_tillNextAttack = ATTACK_DELAY;
		}
	}

	// if the enemy has been attacked ( for health update ) 
	if(m_hasBeenAttacked){
		// decrease value
		m_tillNextUpdate -= 100 * dt;
		// check to make sure it don't go below 0
		if(m_tillNextUpdate < 0) {m_tillNextUpdate = 0;}
		// if 0 reset the value and allow attacking again
		if(m_tillNextUpdate==0){
			m_hasBeenAttacked = false;
			m_tillNextUpdate = UPDATE_HEALTH_DELAY;
		}
	}

	// if the enemy has been chasing the player when attacked without initiating it
	if(m_attackChase){
		// decrease value
		m_tillNextChase -= 100 * dt;
		// check to make sure it don't go below 0
		if(m_tillNextChase < 0) {m_tillNextChase = 0;}
		// if 0 reset the value and allow attacking again
		if(m_tillNextChase==0){
			m_attackChase = false;
			m_tillNextChase = UPDATE_HEALTH_DELAY;
		}
	}

	// Update the enemy According to its current health
	UpdateEnemy();
}

/* Update the enemy according to its current health value */ 
void Enemy::UpdateEnemy()
{
	switch (mHealth)
	{
			// Turn Orange for the 1st attack
	case 2: m_r = 1; m_g = 0.5f; m_b = 0.0f; break;
			// Turn Red for the second attack
	case 1: m_r = 1; m_g = 0.0f; m_b = 0.0f; break;
	case 0: // Create a Particle Effect when Dieing ( An explosion effect by combination of 3 effects)
			// Obtain the current enemy position and raise the y to place the explosion properly
			CVector3 newP = mPosition;
			newP.y += 15;
			// Create a Explision Particle ( A bit like sparks)
			ExplosionParticle* particle = new ExplosionParticle(150, newP, 500);
			particle->SetupParticles();
			// Create A Explosion Fire particles
			ExplosionFireParticle* fireParticle = new ExplosionFireParticle(100, newP, 200);
			fireParticle->SetupParticles();
			// Create the Smoke Explosion particle 
			ExplosionSmokeParticle* smokeParticle = new ExplosionSmokeParticle(250, newP, 50);
			smokeParticle->SetupParticles();

			// Add the three particles effects to the game world
			mWorld->AddGameObject(particle);
			mWorld->AddGameObject(fireParticle);
			mWorld->AddGameObject(smokeParticle);
			// Remove this object
			mWorld->RemoveGameObject(this);
			break;
	}

	SetColor(m_r, m_g, m_b);
}

/* Update the current state of the enemy ( Includes some fuzzy logic ) */ 
void Enemy::UpdateEnemyState(float distance, float dt)
{
	// If state ATTACKED and health value is 1 then increase the speed by 3
	if (mState == ATTACKED && mHealth == 1)
	{  speedMultiplier = 3; }
	// if the player has "ATTACKED" the enemy and the enemy is stil chasing the player and
	// mHealth != 0 to make sure enemy does not shoot when he dies
	else if (mState == ATTACKED && m_attackChase && mHealth != 0)
	{}
	// if the magnitude is less than the percept distance of the enemy change state to chase
	// also if the health is at its lowest increase its speed (very aggressive)
	else if(distance < PERCEPT_DISTANCE && mHealth == 1)
	{	mState = CHASE; speedMultiplier = 3; }
	// if the magnitude is less than the percept distance of the enemy change state to chase
	else if(distance < PERCEPT_DISTANCE)
		mState = CHASE;
	// if magnitude is less than the ranged attacking percept and health is in the middle then
	// increase the speed slightly but alwaays chase the player
	else if ( distance < SHOOT_PERCEPT_DISTANCE && mHealth == 2)
	{	mState = CHASE; speedMultiplier = 1.5; }
	//  if magnitude is less than the ranged attacking percept distance then the enemy starts to shoot standing still
	else if(distance < SHOOT_PERCEPT_DISTANCE)
		mState = ATTACK;
	else
		// otherwise wander around
		mState = WANDER;
}

/* Shoot A bullet */ 
void Enemy::ShootBullet(CVector3 direction)
{
	// If the shot did not complete recently
	if(!m_hasShot){
		// Preset an acceleration
		float bullet_acceleration = 150.0f;
		// Determine velocity
		CVector3 velocity =  direction * bullet_acceleration;
		// increate the y position to position the bullet properly
		CVector3 shootPosition = mPosition;
		shootPosition.y += 10;
		// Create new Shoot Object with enemy position and the velocity worked out
		Shoot* enemyShoot = new Shoot("enemybullet", shootPosition, velocity, 100);
		enemyShoot->SetColor(1.0, 0.0, 0.0);
		enemyShoot->SetTimeToLive(100);
		// Add to the world
		mWorld->AddGameObject(enemyShoot);
		mWorld->AddCollisionEntity(enemyShoot);
		// enemy has shot recently
		m_hasShot = true;
	}
}

// Attack the Player without moving but turning
void Enemy::Attack()
{
	// Dividing the "mChaseVector / value" as for some reason the unit vector seems to go over 1
	// which means that the enemy instantly is on top of the player
	CVector3 direction = mChaseVector / 100;
	// Set y to 0 so the enemy doesnt move upwards
	direction.y = 0.0f;
	// A safety check to make sure no normalizations occur when length is 0
	if(direction.Length() > 0)
		direction.Normalize();

	// Set the velocity of the enemy (in this case 0 as we do not want him to move) 
	mVelocity = CVector3(0, 0, 0);

	/*
		|\     f = forward vector
		|a\    d = direction vector
		|  \   a = angle between the two
		|   \
		|    \
		f     d
		Formula to obtain the angle is :
		arccos(|f|*|d|) = a, 
		a - given in radians so i will need to convert to degrees

		Forward vector will always be (0, 0, 1) where direction changes so the right angle then
		is always worked out (NOTE: When i equaled the forward vector to the previous
		direction, the rotations were not happening as intended). 
	*/  
	float dot = mForward.Dot(direction);
	float radianAngle = static_cast<float>(acos(dot));
	turnAngle = RAD2DEG*radianAngle;

	// If the direction x is negative turn the angle negative so that the rotation occurs on that side
	// (NOTE: Without this the rotation does not occur on the -x side and only occurs on +x , but this also means
	// the enemy does a full 360 turn to face a certain angle as you would have seen in game) 
	if(direction.x < 0)
		turnAngle *= -1;
	
	// Shoot towards the direction specified  
	ShootBullet(direction); 
}

/* Allow the Enemy to Wander Randomly in a direction away from its starting position */
void Enemy::Wander()
{
	// Obtain the direction to wander to
	// (NOTE: Right at the beginning when game starts wanderDestPosition = mPosition )
	CVector3 wanderVect = wanderDestPosition - mPosition;
	// Set the y value to 0, so it does not move upwards
	wanderVect.y = 0.0f;
	// obtain the magnitude of the vector
	float wanderLength = wanderVect.Length();

	// when the position gets close to the final wander position
	if(wanderLength < EPSILON_DISTANCE)
	{
		// Generate a new Random Positon
		if(wanderMovesCount < WANDER_MAX_MOVES)
		{
			wanderDestPosition = mPosition + RandomPosition();
			// Add the number of moves made
			wanderMovesCount++;
		}
		// Or go back to the start position
		else
		{
			wanderDestPosition = wanderStartPosition;
			// reset the number of moves again
			wanderMovesCount = 0;
		}
	}
	// A check to make sure that no normalization is done if magnitude is 0 or less
	if(wanderVect.Length() > 0)
		wanderVect = wanderVect.Normalize();
	
	// Move the Enemy
	Move(wanderVect);
}

/* Chase the player */ 
void Enemy::Chase(float dt)
{
	// Dividing the "mChaseVector / value" as for some reason the unit vector seems to go over 1
	// which means that the enemy instantly is on top of the player
	CVector3 direction = mChaseVector / 100;
	// Set y to 0 so the enemy doesnt move upwards
	direction.y = 0.0f;
	// A safety check to make sure no normalizations occur when length is 0
	if(direction.Length() > 0)
		direction.Normalize();
	// Move the enemy towards the player
	Move(direction);
	// Shoot towards the player
	ShootBullet(direction);
}

/* Move the enemy and Rotate the Enemy in the desired direction */ 
void Enemy::Move(CVector3 direction)
{
	// Set the velocity of the enemy 
	mVelocity = direction * MOVE_CONSTANT * speedMultiplier;

	/*
		|\     f = forward vector
		|a\    d = direction vector
		|  \   a = angle between the two
		|   \
		|    \
		f     d
		Formula to obtain the angle is :
		arccos(|f||d|) = a, 
		a given in radians so i will need to convert to degrees

		Forward vector will always be (0, 0, 1) where direction changes so the right angle then
		is always worked out (TROUBLE: When i equaled the forward vector to the previous
		direction, the rotations were not happening as intended). 
	*/ 
	float dot = mForward.Dot(direction);
	float radianAngle = static_cast<float>(acos(dot));
	turnAngle = RAD2DEG*radianAngle;

	// If the direction x is negative turn the angle negative so that the rotation occurs on that side
	// (NOTE: Without this the rotation does not occur on the -x side and only occurs on +x , but this also means
	// the enemy does a full 360 turn on a certain angle to turn to that specific angle as you would have seen in game) 
	if(direction.x < 0)
		turnAngle *= -1;
}

/* Obtain a Random Position Vector to be used for wandering */ 
CVector3 Enemy::RandomPosition()
{
	// initialize the custom random class
	r.Randomize();
	// Obtain random x, z values which have to be a minimum of the wander distance
	float x = WANDER_DISTANCE + static_cast<float>(r.Random(50));
	float y = 0.0f;
	float z = WANDER_DISTANCE + static_cast<float>(r.Random(50));

	// Randomly choose if x is positive of negative
	int xRandom = r.Random(2);
	if(xRandom == 1)
		x *= -1;
	// Randomly choose if z is positive of negative
	int zRandom = r.Random(2);
	if(zRandom == 1)
		z *= -1;

	CVector3 random = CVector3(x, y, z);
	// return the random vector
	return random;
}

/* Test Collisions to see if it has collided */ 
bool Enemy::CollisionTest(Entity* o)
{
	if(o->GetType() == GameObjectType("bullet") || o->GetType() == GameObjectType("player") || 
		o->GetType() == GameObjectType("redsquare2") ||  o->GetType() == GameObjectType("bluesquare2") || 
		o->GetType() == GameObjectType("yellowsquare2") || o->GetType() == GameObjectType("enemy")) 
		return mBoundingSphere->CollisionTest(o->GetBoundingShape());
	return false;
}

/* If a Collision does occur then */ 
void Enemy::OnCollision(Entity* o)
{
	if(o->GetType() == GameObjectType("bullet")){
		// A check to make sure that not too many updates occur while collision is being updated.
		// This is due to the bullet stil being inside the enemy bounding sphere this causes the health
		// value to rapidly go down to 0 without allowing 3 attacks. So this checks with a countdown that makes sure
		// only only collision is read for an update to occur
		if(!m_hasBeenAttacked){
			// decrease health value
			mHealth--;
			m_hasBeenAttacked = true;
			mState = ATTACKED;
			// tell the enemy to chase the player
			m_attackChase = true;
		}
	}
	if(o->GetType() == GameObjectType("player")){
		// A check to make sure that health is not complelty wiped out
		if(!m_hasAttacked){
			FireEnemyAttack();
			m_hasAttacked = true;
		}
	}

	if(o->GetType() == GameObjectType("redsquare2") ||  o->GetType() == GameObjectType("bluesquare2") || 
		o->GetType() == GameObjectType("yellowsquare2") || o->GetType() == GameObjectType("enemy"))
		// Do not allow the enemy to walk though these objects and instead "bounce" off them
		m_Bounce = true;
}
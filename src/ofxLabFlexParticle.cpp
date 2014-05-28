//
//  Particle.cpp

#include "ofxLabFlexParticle.h"

using namespace lab;

Particle::Particle()
{
    setDefaults();
    set(0.0f, 0.0f);
}

Particle::Particle( const ofVec2f& pos )
{
    setDefaults();
    set(pos);
}

Particle::Particle( float x, float y ){
    setDefaults();
    set(x,y);
}

Particle::Particle( const ParticleOptions& opts ){
    setDefaults();
	set(opts.pos);
	damping  = opts.damping;
	radius	 = opts.radius;
	rotation = opts.rotation;
	velocity = opts.velocity;
	rotateVelocity = opts.rotateVelocity;
}

void Particle::setDefaults(){
    radius = 2;
    damping = 1.0f;
    mass = 1;
    age = 0;
    startSecond = ofGetElapsedTimef();
    uniqueID = 0;
    data = NULL;
}

void Particle::update(){
    age++;
    
	// update position and rotation
    velocity += acceleration;
    acceleration *= 0;
    velocity *= damping;
    rotation += rotateVelocity;
    rotateVelocity *= damping;
	
    *this += velocity;
	//cout << (*this) << endl;
}

void Particle::draw(){

    ofSetColor(255, 255, 255);
	ofCircle(*this, radius );

    ofSetColor(0);
    ofDrawBitmapString(ofToString(uniqueID), x - 10, y );
}

void Particle::repel(const Particle& b)
{
    // TODO this should be explored, right now it's pretty straight forward
    // and probably doesn't even work that great
 
    float distance = ofDist(x, y, b.x, b.y);
    
    if( distance > b.radius + radius ) {
        return;
    }
    
    // ofVec2f - ofVec2f
    ofVec3f diff = ofVec3f::operator-( b );
    
    diff.normalize();
    
    // http://www.grantchronicles.com/astro09.htm
    // this is a really lose interpretation.. like not very close
    float force = b.mass * mass / MAX(1, distance);
    float accel = force / mass;
    
    acceleration += diff * accel;
}


Particle& Particle::operator=(const Particle& p)
{
    ofVec3f::operator=(p);
    damping  = p.damping;
    radius	 = p.radius;
    rotation = p.rotation;
    velocity = p.velocity;
    rotateVelocity = p.rotateVelocity;
    
    return *this;
}

void Particle::setAge( int _age ){
    age = _age;
}

int Particle::getAge(){
    return age;
}

float Particle::getStartSeconds() {
    return startSecond;
}

void * Particle::getData(){
    return data;
}

void Particle::setData( void * data ){
    this->data = data;
}

unsigned long Particle::getUniqueID()
{
    return uniqueID;
}

void Particle::setUniqueID( unsigned long id )
{
    uniqueID = id;
}




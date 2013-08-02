#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground( 10, 10, 10);
	
	camera.setPosition(ofVec3f(0, -7.f, -10.f));
	camera.lookAt(ofVec3f(0, 0, 0), ofVec3f(0, -1, 0));

	world.setup();
	world.enableGrabbing();
	world.enableDebugDraw();
	world.setCamera(&camera);
	
	sphere = new ofxBulletSphere();
	sphere->create(world.world, ofVec3f(0, 0, 0), 0.1, .25);
	sphere->add();
	
	box = new ofxBulletBox();
	box->create(world.world, ofVec3f(7, 0, 0), .05, .5, .5, .5);
	box->add();
	
	cone = new ofxBulletCone();
	cone->create(world.world, ofVec3f(-1, -1, .2), .2, .4, 1.);
	cone->add();
	
	capsule = new ofxBulletCapsule();
	capsule->create(world.world, ofVec3f(1, -2, -.2), .4, .8, 1.2);
	capsule->add();
	
	cylinder = new ofxBulletCylinder();
	cylinder->create(world.world, ofVec3f(0, -2.4, 0), .8, .9, 1.8);
	cylinder->add();
	
	// set quaternion, so we know which way is up //
    ofQuaternion groundQuat;
    groundQuat.set(0, 1, 0, 1.);
    ground.create( world.world, ofVec3f(0., 5.5, 0.), groundQuat, 0., 10.f, 1.f, 10.f );
    ground.setProperties(.25, .95);
    ground.add();
    // allows manipulation of object. The object will not react to other objects, but will apply forces to them //
    // just like a static object, except you can move it around //
    ground.enableKinematic();
}

//--------------------------------------------------------------
void testApp::update() {
	world.update();
	ofSetWindowTitle(ofToString(ofGetFrameRate(), 0));
    
    // store the position of the ground //
    ofVec3f pos = ground.getPosition();
    
    // create a bullet transform object and set the position to that of the object //
    btTransform trans;
    trans.setOrigin( btVector3( btScalar(pos.x), btScalar(pos.y), btScalar(pos.z)) );
    
    // get the rotation quaternion from the ground //
    ofQuaternion rotQuat = ground.getRotationQuat();
    // print out the angle
    cout << "rotation " << rotQuat.w() << endl;
    float newRot = rotQuat.w();
    // rotate it a bit //
    newRot += .01f;
    // clamp values between PI and -PI so there is no jumping //
    if(newRot >= PI) newRot -= PI;
    if(newRot <= 0) newRot += PI;
    
    // set the rotation of the bullet transform to that of the axis of the stored quaternion
    // and apply the new rotation
    trans.setRotation( btQuaternion(btVector3(rotQuat.x(), rotQuat.y(), rotQuat.z()), newRot) );
    // apply the transform to the rigid body //
    ground.getRigidBody()->getMotionState()->setWorldTransform( trans );
    // tell the ofxBulletWorldRigid that we have moved rigid body and it should update the collision object //
    ground.activate();
}

//--------------------------------------------------------------
void testApp::draw() {
	glEnable( GL_DEPTH_TEST );
	camera.begin();
	
	ofSetLineWidth(1.f);
	ofSetColor(255, 0, 200);
	world.drawDebug();
	
	ofSetColor(100, 100, 100);
	ground.draw();
	
	ofSetColor(225, 225, 225);
	sphere->draw();
	
	ofSetColor(225, 225, 225);
	box->draw();
	
	ofSetColor(225, 225, 225);
	cylinder->draw();
	
	ofSetColor(225, 225, 225);
	capsule->draw();
	
	ofSetColor(225, 225, 225);
	cone->draw();
	
	camera.end();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y) {
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h) {
	
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg) {
	
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo) { 
	
}
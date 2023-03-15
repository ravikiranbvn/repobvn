// solution to https://developers.google.com/edu/c++/next-steps Example #1
#include <iostream>
#include <random>
#include <time.h>
#include <math.h>

using namespace std;

const int kNumShells = 10;  // allowed 10 shells per target
const int kMinDist = 200;  // min distance for a target
const int kMaxDist = 900;  // max distance for a target
const double kVelocity = 200.0;  // initial velocity of 200 ft/sec
const double kGravity = 32.2;  // gravity for distance calculation
const double kPi = 3.1415;

// Returns the distance a shot travels given its angle.
int DistanceCalc (double in_angle) {

  double time_in_air;
  // The following calculates how far the shot goes given
  // its angle of projection, velocity, and how long it stays
  // in the air.
  time_in_air = (2.0 * kVelocity * sin(in_angle)) / kGravity;
  return (int) round((kVelocity * cos(in_angle)) * time_in_air);
}

// Get user's angle input and calculates distance where shot lands.
// Returns the distance the shot lands.
int CheckShot() {

  int distance;
  double angle;
  cout << "What angle? " << endl;
  if (!(cin >> angle))
    return -1;

  // Convert to radians.
  angle = (angle * kPi) / 180.0;
  distance =  DistanceCalc(angle);
  return distance;
}

// Generate a random number for the enemy position.
int Initialize() {
  int enemy_position;

  // Initialize random seed.
  srand (time(NULL));

  // Generate random number between kMinDist and kMaxDist
  enemy_position = rand() % kMaxDist + kMinDist;
  cout << "The enemy is " << enemy_position << " feet away!!!" << endl;
  return enemy_position;
}

// This function plays the game
void Fire() {
  int enemy, shots, hit;
  int distance;
  static int number_killed = 0;

  // Initialize variables.
  shots = kNumShells;
  enemy = Initialize();
  distance = 0;
  hit = 0;

  do {
    // Get the distance where shot lands & compare it to enemy position.
    distance = CheckShot();
    // Some error checking on the input.
    if (distance == -1) {
      cout << "Enter numbers only..." << endl;
      cin.clear();
      cin.ignore(10000,'\n');
      continue;
    }
    // Compare the enemy position with the computed distance.
    if (abs(enemy - distance) <= 1) {
      hit = 1;
      number_killed++;
      cout << "You hit him!!!" << endl;
      cout << "It took you " << kNumShells - shots + 1 <<  " shots." << endl;
      cout << "You have killed " <<  number_killed << " enemies." << endl;
    } else {
      shots--;
      if (distance > enemy) {
        cout << "You over shot by " << abs(enemy - distance) << endl;
      } else {
        cout << "You under shot by " << abs(enemy - distance) << endl;
      }
    }
  } while ((shots > 0) && (!(hit)));
  if (shots == 0)
    cout << "You have run out of ammo..." << endl;
}

int main()
{
    char done;

    cout <<  "Welcome to Artillery." << endl;
    cout << "You are in the middle of a war and being charged by thousands of enemies." << endl
          <<  "You have one cannon, which you can shoot at any angle." << endl
          <<  "You only have 10 cannonballs for this target.." << endl
          <<  "Let's begin..." << endl;

    do {
      Fire();
      cout << "I see another one, care to shoot again? (Y/N) " << endl;
      cin >> done;
    } while (done != 'n');

    return 0;
}
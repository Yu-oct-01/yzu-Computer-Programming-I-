#include <iostream>
#include <fstream>
using namespace::std;

struct Member
{
   char email[ 40 ];
   char password[ 24 ];
   char IDNumber[ 12 ];
   char name[ 12 ];
   char phone[ 12 ];
};

void loadMemberInfo( ifstream &inMemberFile, Member memberDetails[], int &numMembers );

// input an integer from the keyboard, and
// returns the integer if it belongs to [ begin, end ], returns -1 otherwise.
int inputAnInteger( int begin, int end );

void login( Member memberDetails[], int numMembers );

// returns true if there is a member
// whose email and password are equal to the specified email and password, respectively
bool legal( char email[], char password[], Member memberDetails[], int numMembers, int &recordNumber );

void accountInfor( Member memberDetails[], int numMembers, int recordNumber );

void newMember( Member memberDetails[], int &numMembers );

// returns true if there is a member whose IDNumber is equal to newIDNumber
bool existingID( char newIDNumber[], Member memberDetails[], int &numMembers );

// returns true if there is a member whose email is equal to newEmail
bool existingEmail( char newEmail[], Member memberDetails[], int &numMembers );

void saveMemberInfo( ofstream &outMemberFile, Member memberDetails[], int numMembers );

int main()
{
   Member memberDetails[ 100 ] = { "", "", "", "", "" };
   int numMembers = 0;

   ifstream inMemberFile;
   ofstream outMemberFile;

   loadMemberInfo( inMemberFile, memberDetails, numMembers );

   cout << "Welcome to Vieshow Cinemas member system\n\n";

   int choice;

   while( true )
   {
      cout << "Enter your choice:" << endl;
      cout << "1. Sign In\n";
      cout << "2. New Member\n";
      cout << "3. Sign Out\n? ";

      choice = inputAnInteger( 1, 3 );
      cout << endl;

      switch( choice )
      {
      case 1:
         login( memberDetails, numMembers );
         break;

      case 2:
         newMember( memberDetails, numMembers );
         break;

      case 3:
         saveMemberInfo( outMemberFile, memberDetails, numMembers );
         cout << "Thank you...\n\n";
         system( "pause" );
         return 0;

      default:
         cout << "Input Error!\n\n";
         break;
      }
   }

   system( "pause" );
}
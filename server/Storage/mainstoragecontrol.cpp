#include "mainstoragecontrol.h"
using namespace std;

MainStorageControl::MainStorageControl(QObject *parent)
    : QObject(parent)
{
    /*contentControl = new ContentStorageControl(this);
    courseControl  = new CourseStorageControl(this);
    orderControl   = new OrderStorageControl(this);
    userControl    = new UserStorageControl(this);*/
}


bool getUser(int userid, User user, string errorMsg){
    // Query:

    // Send query to DB TODO: Function for running queries
    // Get back the result
    // Is the error message neccessary for this one? Maybe not.
    // Set User to null if not found - better yet return false, set user to null and errorMsg = '';
    // Error message is useful if there's a db connection problem.
    // Otherwise create a new user, set user equal to newUser return true.
}

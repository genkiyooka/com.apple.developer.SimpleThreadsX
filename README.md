# SimpleThreadsX
This sample demonstrates a simple use of the Cocoa threading APIs, including the use of Distributed Objects (DO) to coordinate multiple pre-emptively scheduled secondary threads with the non-reentrant Cocoa framework. 

## 2023 Updates
- Created Xcode projects for Xcode 5.1.1 and Xcode 14
- Sandboxed and migrated XIB to modern format
- Discovered and fixed springs & struts layout bug (button labeled 'Kill Inactive Threads')
- Reverse migrated XIB layout fix back to Panther 10.5 and Xcode 3.1


###Read Me About SimpleThreads

1.0d5

This sample demonstrates a simple use of the Cocoa threading APIs, including the use of Distributed Objects (DO) to coordinate multiple pre-emptively scheduled secondary threads with the non-reentrant Cocoa framework.

Note: The TrivialThreads sample is required reading for this sample; you will not understand this sample unless you understand TrivialThreads.

#####Background

In the TrivialThreads sample I showed how to create a secondary pre-emptively scheduled thread and then use Distributed Objects (DO) to coordinate progress updates with the non-reentrant Cocoa framework.  This sample extends TrivialThreads to provide multiple secondary threads, each of which runs independently and can communicate with the main thread using DO.

#####High Level Structure

The sample contains the following classes:

- Controller – This is the primary controller for the application.  There is one instance of this class which is instantiated in the main NIB file, and wired up to the user interface via Interface Builder.  When you click on a button in the window, the instance creates a secondary thread and connects to an object (of class TransferServer) in that thread via Distributed Objects.  It then calls a method on the transfer server object to do the slow operation, which executes the operation on the secondary thread.
- TransferServer – This class contains the code for the server object.  When the connectToPorts: method is invoked it is running in a secondary thread.  That method sets up the DO connection back to the application thread and then enters the run loop and waits for DO requests.

#####User Level Operation

The compiled version of this sample was built for a pre-Developer release of Rhapsody (ie OpenStep/Mach 4.2 for Intel + Yellow 1H). Your mileage may vary.

To see the sample in action, simply launch SimpleThreads.app from Workspace.  You will see a window with two test buttons and an output text view.  When you click on the ™Something Slow∫ button, the sample starts a slow operation in a secondary thread.  This operation involves the thread repeatedly sleeping and outputing progress information to the text view.  The clever thing is that the main application thread starts the operation through a DO message to the secondary thread, and the secondary thread updates the output text view by sending a DO message back to the main thread (thereby avoiding AppKit re-entrancy problems).

The ™Something Slower∫ button is similar to the ™Something Slow∫ button except that its operation is even slower.

Note that, unlike TrivialThreads, you can click on the buttons repeatedly and get multiple threads, each of which is running in parallel.  Whenever a thread prints progress information, it tags the information with an ™ID∫ so that you can thread the output for a single operation together.

#####Building the Code

The code was built for Intel on pre-Developer release of Rhapsody (ie OpenStep/Mach 4.2 for Intel + Yellow 1H). Your mileage may vary.

As far as I know this code does not use any Rhapsody-specific constructs, and should build just fine in other OpenStep 4.2 environments.

To build the code, launch the ™PB.project∫ file inside the ™SimpleThreads∫ folder. After the project opens, choose ™Build∫ from the ™Project Build∫ submenu of the ™Tools∫ menu. When the build finishes, choose ™Run∫ from the ™Launcher∫ submenu of the ™Tools∫ menu to execute the code.

#####Restrictions and Caveats

When a thread finishes an operation it does not die.  Instead it sends a message to the main thread to let it know that the thread is free for new operations, and returns to its run loop waiting for new commands.  The main thread keeps track of which threads are free for new operations and, when a new operation is started, reuses a free thread if it can.  

In some case this could be considered good design; it's common for thread creation to be expensive, and thus it often makes sense to keep of bunch of `worker' threads around.  However, in the current implementation, the number of threads in place is equal to the maximum number of threads that have ever been used concurrently.  The pool of threads never shrinks, even if the load drops radically.  This could be very wasteful of resources.

Related to this caveat is the fact that the sample does not shut down properly.  When you deallocate the Controller object, it leaves all its TransferServer, NSThread and NSConnection objects behind.  This is not a problem in practice (the only way for the Controller to be deallocated is when the application shuts down), but I would like to revisit this design at some stage when I know more about how to clean up properly.

My final caveat is that I don't handle torn connections well.  NSConnections can be run over the network, and hence are subject to tearing through network failures.  Normally you would have to watch for this by observing the NSConnectionDidDieNotification, however I've made the simplifying assumption that this won't happen for local connections between threads.  This is tied in with shutting down properly, something that I haven't quite mastered yet.

##### Coding Notes

The source code is heavily commented.  For more information about the specifics of the design, take a look at the comments.

##### See Also

For more information about Distributed Objects, check out the reference documentation for the following classes: NSConnection, NSRunLoop, and NSThread.

Credits and Version History

Version 1.0d1 was distributed for review inside Apple.

Version 1.0d2 is the first widely released version.  It includes some cosmetic code changes.

Version 1.0d3 added code to make sure that the main window is active after launch [Radar ID 1683474].

Version 1.0d4 fixed a few threading bugs, properly disposes of threads when the application exits, and updates to the latest interface guidelines.

Version 1.0d5 Updated for Project Builder on Mac OS X

Share and Enjoy.

###Quinn ™The Eskimo!
Apple Worldwide Developer Technical Support

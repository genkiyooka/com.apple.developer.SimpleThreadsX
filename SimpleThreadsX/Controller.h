/*    File:       Controller.h    Contains:   Central control object for sample.    Written by: Quinn "The Eskimo!"    Created:    Tue 10-Jun-1997    Copyright:  (c)1997 by Apple Computer, Inc., all rights reserved.    Change History (most recent first):    You may incorporate this sample code into your applications without    restriction, though the sample code has been provided "AS IS" and the    responsibility for its operation is 100% yours.  However, what you are    not permitted to do is to redistribute the source as "DSC Sample Code"    after having made changes. If you're going to re-distribute the source,    we require that you make it clear in the source that the code was    descended from Apple Sample Code, but that you've made changes.*/#import <AppKit/AppKit.h>// IMPORTANT: See the documentation ("ReadMe.rtf" under Supporting Files) for// big picture information about this project.@class TransferServer;@interface Controller : NSObject{    // Interface Builder connections.    id mainWindow;    id textField;    id infoPanel;    // Set up in our init method.    NSMutableArray *freeServers;        // An array of TransferServer objects that currently have nothing to do.}- (id)init;    // Initialises the controller object; the only part of this is the    // creation of an empty freeServers array.- (oneway void)outputString:(bycopy NSString *)theString;    // Appends theString to the output text field.  This routine is    // callable both by the controller object running in the main    // thread, and by the server object running in a secondary thread.    // The "oneway" type qualifier informs the Distributed Object    // system that it does not have to wait for this message to be    // delivered before letting the sender continue running.  This    // is a sensible thing to do for things like updating progress    // information, because you don't want your threaded operation    // to stop and wait to synchronise with the main thread just so    // that you can confirm that the progress bar has been updated    // correctly.- (void)serverFinished:(TransferServer *)server;    // The server objects call this method when they are done.    // This requeues the server object on to freeServers, where    // it will be available for reuse for some other request.// Interface Builder Actions- (void)doSomethingSlow:(id)sender;    // Called when the "Something Slow" button is clicked.    // It finds a free transfer server, creating one if there    // are none free, and requests it to do a slow operation.- (void)doSomethingSlower:(id)sender;    // Similar to doSomethingSlow except that it's wired to    // the "Something Slower" button and causes the server    // to do something slower than slow.- (void)killThreads: (id)sender;    // This function disposes all threads that aren't presently    // running a transaction.  This is used to show how to    // properly dispose of the remote threads.- (void)showAboutPanel: (id) sender;@end
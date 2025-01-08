# Text Editor Implementation

## Description

A console-based text editor implemented in C++ using a hybrid data structure approach. The editor features a mode-based interface, cursor system, and supports basic text editing operations. The implementation provides a solid foundation for a text editor with a clear separation of concerns and extensible architecture.

## Architecture Overview

The text editor is implemented using a hybrid data structure approach that combines:

•	A vector of lines (vector<LinkedList>)
•	Doubly-linked lists for each line of text
•	A cursor system tracking both line position and character position

## Key Design Choices

1.	Data Structure Selection 
o	Lines are stored in a vector for O(1) random access between lines
o	Each line uses a doubly-linked list to efficiently handle character insertion/deletion
o	The doubly-linked list enables bi-directional cursor movement within lines
2.	Mode-based Interface 
o	Implements a simplified vim-like modal interface with Normal and Insert modes
o	Normal mode for navigation and commands
o	Insert mode for text entry
o	Reduces complexity of handling keyboard input by separating concerns
3.	Cursor Implementation 
o	Maintains two cursor coordinates: 
	currentLine: Index into the lines vector
	charCursor: Pointer to current character node
o	Visual feedback through '|' character display

## Technical Decisions

1.	LinkedList Class Design 
o	Encapsulates line management
o	Maintains head/tail pointers for efficient end operations
o	Provides clean interface for character insertion and display
2.	TextEditor Class Design 
o	Handles high-level operations and state management
o	Manages mode switching
o	Coordinates between line and character operations
3.	Input Handling 
o	Uses _getch() for immediate character input without buffering
o	Translates arrow key inputs into consistent codes
o	Separates input handling from editor logic

## Implementation Challenges

1.	Cursor Management 
o	Challenge: Maintaining correct cursor position during line transitions
o	Solution: Reset cursor to line end when moving between lines
o	Limitation: Could be improved to maintain relative cursor position
2.	Input Handling Complexity 
o	Challenge: Different systems represent special keys differently
o	Solution: Implemented translation layer in getChar()
o	Limitation: Platform-dependent due to _getch() usage
3.	Display Refresh 
o	Challenge: Efficient screen updates without flickering
o	Solution: Full screen refresh using system("cls")
o	Limitation: Not optimal for performance, could use more sophisticated terminal handling

## Potential Improvements

1.	Memory Management 
o	Add proper destructor to handle linked list cleanup
o	Implement copy constructor and assignment operator
2.	Text Operations 
o	Add delete/backspace functionality
o	Implement copy/paste operations
o	Add text selection capabilities
3.	Performance Optimizations 
o	Implement partial screen updates
o	Add text buffer for handling larger files
o	Optimize line splitting/joining operations
4.	Cross-platform Compatibility 
o	Replace platform-specific calls with portable alternatives
o	Abstract terminal handling into separate class
o	Add configuration for different terminal types

## Conclusion

The current implementation provides a solid foundation for a text editor with a clear separation of concerns and extensible architecture. While there are limitations and areas for improvement, the core design choices support the basic functionality required for text editing operations.
The use of linked lists for lines balances memory usage with insertion performance, while the vector of lines provides quick random access for vertical navigation. The mode-based interface simplifies input handling and provides a familiar paradigm for users of traditional text editors.

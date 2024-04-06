<h1 align="center">🎉 TETRIS: A C++ Console Experience 🎉</h1>

<p align="center">
 Tetris is a video game everyone's heard of and played. Recognized for its simplicity, intuitiveness, and surprisingly addictive nature, Tetris exists in a variety of versions for a variety of devices. The aim of my Tetris program is to provide an object-oriented implementation of this basic game into the console. Using features such as OOP, inheritance, composition, operator overloading, and file management, my implementation will integrate everything we have learnt in class this year to ensure its smooth functioning. 
  <br />
  <a href="https://github.com/AndyDerevyanko/Console-Tetris/issues">Report Bug</a>
  ·
  <a href="https://github.com/AndyDerevyanko/Console-Tetris/issues">Request Feature</a>
</p>

## 📚 Table of Contents


- [What is TETRIS?](#-what-is-tetris)
- [Controls](#-controls)
- [Working Demo](#-working-demo)
- [Features](#-features)
- [Implementation](#-implementation)
- [UML Diagrams](#-uml-diagrams)
- [PERT Chart](#-pert-chart)

## 🌟 What is TETRIS?

<p align="left">
  <img src="https://raw.githubusercontent.com/AndyDerevyanko/Console-Tetris/main/images/logo.png" alt="tetris logo" width="80" height="80">
</p>

Tetris, created in 1985 by Soviet software engineer Alexey Pajitnov, is a renowned puzzle video game. Initially published by Nintendo, the rights later reverted to Pajitnov in 1996, leading to the formation of the Tetris Company with Henk Rogers for licensing management. The game involves arranging tetrominoes to complete lines, earning points as lines disappear. The goal is to prevent uncleared lines from reaching the top. With simple rules, Tetris became a video game masterpiece, selling 202 million copies by December 2011 and holding a Guinness world record for the most ported game on over 65 platforms. Its influence extends to popular culture, architecture, music, and cosplay, while research studies explore its theoretical complexity and the Tetris effect on the human brain.

## 🌟 Controls

A - Move block left
D - Move block right
Z - Rotate block counter-clockwise
C - Rotate block clockwise

Spacebar - Drop block Instantly 

## 🌟 Working Demo

Try out a working demo [here](https://onlinegdb.com/ziifCCCxY).

<p align="left">
  <img src="https://raw.githubusercontent.com/AndyDerevyanko/Console-Tetris/main/images/demo.png" alt="demo" width="80" height="80">
</p>

## 🌟 Features

- Fully working NES Tetris on console
- All features from NES Tetris included
- Score tracking with usernames
- Primitive main menu and exiting system
- Well-structured code comments to explain algorithms

## 🌟 Implementation

This program relies on object-oriented programming. As such, it will contain a variety of different objects. Firstly, we will have the "board" object on which the program relies on, and a "block" object that will be displayed on the board. The “board” object will contain the game state, including the current score, level, lines cleared, and an array representing the layout of blocks on the board. The "block" object, on the other hand, will be a class with various subclasses that represent different Tetris block shapes.

The primary subclasses of the "block" class includes the:
- "reg" (regular block) class: This represents a basic 1x1 block. It will contain two main states: “empty” for an empty cell (on the tetris board) and color, to represent the color of any blocks that are drawn on the board
- "line" class: A subclass representing the long straight block
- "L" class: This represents the L-shaped block
- "LInvert" class: An inverted L-shaped block
- "Square" class: Represents the square-shaped block
- "Z" and "ZInvert" classes: Two subclasses representing the Z-shaped and inverted Z-shaped blocks
- "T" class: Represents the T-shaped block

<p align="left">
  <img src="https://raw.githubusercontent.com/AndyDerevyanko/Console-Tetris/main/images/blocks.png" alt="demo" width="80" height="80">
</p>

## 🌟 UML Diagrams
UML Diagrams for each object are available below:

### Full UML Diagram ###
<p align="left">
  <img src="https://raw.githubusercontent.com/AndyDerevyanko/Console-Tetris/main/images/UML.png" alt="demo" width="80" height="80">
</p>

### Block UML Diagram ###
<p align="left">
  <img src="https://raw.githubusercontent.com/AndyDerevyanko/Console-Tetris/main/images/block_UML.png" alt="demo" width="80" height="80">
</p>

### Board UML Diagram ###
<p align="left">
  <img src="https://raw.githubusercontent.com/AndyDerevyanko/Console-Tetris/main/images/board_UML.png" alt="demo" width="80" height="80">
</p>

Resizable UML Diagrams available [here](https://lucid.app/documents/embedded/16168ae7-fb5a-42fa-bc3c-af2b0953bbe6?invitationId=inv_99255cb7-6d88-42b1-afd3-2ac65b9d8ba7#)


## 📊 PERT Chart
### Interested in how this project was developed?
A PERT chart is shown below. Keep in mind this project was created on REPLIT before being integrated into Github.

<p align="left">
  <img src="https://raw.githubusercontent.com/AndyDerevyanko/Console-Tetris/main/images/PERT.png" alt="demo" width="80" height="80">
</p>

View my REPLIT profile ![here](https://replit.com/@AndyDerevyanko)
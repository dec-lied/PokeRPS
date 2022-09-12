# PokeRPS
<p> 9/12/22 CAS Reflection 8 - PokeRPS (Poke Rock Paper Scissors) </p>

<h1> How to download and execute </h1>
  <p> <b> Note about source code: </b> the dlls are not included in the /pokeRPS folder due to them being architecture dependant. If you want to run the source code yourself, drag the respective dlls from the /standalone/dlls folder into the /pokeRPS folder where main.cpp resides </p>
  <p> I made this project with Visual Studio, using C++20 with Microsoft's MSVC compiler. Other compilers should work but for simplicity I recommend using Visual Studio as well. I use Visual Studio 2022 but older versions will work as well </p>
  <p> To download, install git if not already installed and type the following command in any terminal: </p>

```
git clone https://github.com/dec-lied/PokeRPS.git
``` 

<p> to download the repository. The main code is in the /firstUI folder with the includes being in the /include directory. </p>
<p> You can do either of the following to run the program: </p>
<ol>
  <li> Build it from the source yourself by opening pokeRPS.sln and in Visual Studio, selecting Release as well as x64 or x86 according to your pc architecture then click build. If you decide to do this, be sure to <b> <ins> place the executable pokeRPS.exe into the /standalone folder and pull the architecture respective dlls from the dll folders into the /standalone folder together with pokeRPS.exe. </ins> </b> </li>
  <li> Download the release according to your computer's architecture from the Releases tab on 
  <a href="https://github.com/dec-lied/PokeRPS/releases"> this page </a>. </li>
</ol>

<h1> How to play </h1>
<ul>
  <li> The game will start at the intro screen where you can either start playing or go to the main menu. </li>
  <li> If you do not know how the pokemon type system works, either click tutorial in the game or read below:
  </li>   
  <li> <ins> Fire beats Grass, Grass beats Water, and Water beats Fire. </ins> </li>
  <li> It goes in a circle, just like rock paper scissors! </li>
  <li> Click play to play a round of RPS. Choose a type and watch the outcome! After the round, you will be   returned to the main menu where you can play, learn how to play, or exit. </li>
</ul>

<h1> Features </h1>
<ul>
  <li> This game includes my own UI engine! I do not have a name for it and it is very minimal, but I am proud of   it and it is super easy to use! </li>
  <li> All UI elements fully scale with the window! All elements retain size and position perfectly, and changing   the window size to any ratio will work perfectly! </li>
  <li> Classic gen 1 pokémon music, sprites, and aesthetics! </li>
</ul>

<h1> Screenshots of the game </h1>
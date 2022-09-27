# PokeRPS
<p> 9/12/22 CAS Reflection 8 - PokeRPS (Poké Rock Paper Scissors) </p>

<h1> How to download and execute </h1>
<p> You can do either of the following to run the program: </p>
<ol>
  <li> Download the release according to your computer's architecture from the Releases tab on 
  <a href="https://github.com/dec-lied/PokeRPS/releases"> this page</a>. </li> 
  <b> or </b>
  <li> Build it from the source yourself by opening pokeRPS.sln and in Visual Studio, selecting Release as well as x64 or x86 according to your pc architecture then click build. If you decide to do this, be sure to <b> <ins> place the executable pokeRPS.exe into the /standalone folder and pull the architecture respective dlls from the dll folders into the /standalone folder together with pokeRPS.exe. </ins> </b> </li>
</ol>
  <p> I made this project with Visual Studio, using C++20 with Microsoft's MSVC compiler. Other compilers should work but for simplicity I recommend using Visual Studio as well. I use Visual Studio 2022 but older versions will work as well </p>
  <p> To download, install git if not already installed and type the following command in any terminal: </p>

```
git clone https://github.com/dec-lied/PokeRPS.git
``` 

<p> to download the repository. The main code is in the /pokeRPS folder with the includes being in the /include directory. </p>

<h1> Features </h1>
<ul>
  <li> This game includes my own UI engine! Right now I call it gluey and although it is pretty minimal, I am proud of it and it is super easy to use! </li>
  <li> All UI elements fully scale with the window! All elements retain size and position perfectly, and changing the window size to any ratio will work perfectly! </li>
  <li> Classic gen 1 pokémon music, sprites, and aesthetics! </li>
  <li> User settings that will persist and be saved, allowing the user to keep settings forever! </li>
</ul>

<h1> How to play </h1>
<ul>
  <li> The game will start at the intro screen where you can either see the tutorial or go to the main menu. </li>
  <li> If you do not know how the pokémon type system works, either click tutorial in the game or read below:
  </li>   
  <li> <ins> Fire beats Grass, Grass beats Water, and Water beats Fire. </ins> </li>
  <li> It goes in a circle, just like rock paper scissors! </li>
  <li> Click play to play a round of RPS. Choose a type and watch the outcome! After the round, you will be   returned to the main menu where you can play, learn how to play, or exit. </li>
</ul>

<h1> Screenshots of the game </h1>

![welcome PNG](https://user-images.githubusercontent.com/103293120/192406456-291d6e4d-a879-4fed-b6d9-e1315bb22dbe.png)

![menu PNG](https://user-images.githubusercontent.com/103293120/192406477-2962a1f3-cf8a-4613-8935-ae7217863df0.png)

![battle PNG](https://user-images.githubusercontent.com/103293120/192406484-35a84c31-8d1a-4955-856c-25a84a598cd3.png)

![settings PNG](https://user-images.githubusercontent.com/103293120/192406509-a002b85d-1f5e-479e-b628-823ef0936aaa.png)

![tut PNG](https://user-images.githubusercontent.com/103293120/192406467-543e3572-728f-4610-932f-f74ea7985dda.png)

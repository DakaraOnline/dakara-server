# Dakara Online

Alejandro Santos @alejolp - May 2015.

Dakara Online is a Massively Multiplayer Online Role Playing Game, or MMORPG for short. It is a volunteer-based project of people known to each other only through Internet forums and mailing lists. The game is free to play and requires a personal computer running Microsoft Windows XP or later. The game server is a migration from the original Argentum Online Visual Basic 6.0 source code to the modern C++11 by the means of a source code translator program. The game client source code still remains written in Visual Basic 6.0. The main reason to migrate away from Visual Basic 6.0 is the lack of official support from Microsoft for its tools, compiler, and libraries, which ended in the year 2005. In this document it is described how Dakara Online was created and how is run today.

# Argentum Online

## The early days

Argentum Online is an Online Game first developed by a small group of enthusiasts during the years 2000-2002 in Argentina, and it is believed to be the first game of its kind created by game developers based on the country. Pablo Márquez and Fernando Testa, founders of Noland Studios, were back then the two original authors who in their free time decided to create an online game where people for free would be able to interact and make friends while having fun.

The game quickly gained traction, and by the end of 2001 it became very popular. With 2000 active players, 200 players on average playing, and with peaks of 350 players, the expectations of the developers were exceeded. Some newspapers from Argentina catched up with articles, and those articles can be found (in spanish) in the Vault section of the Argentum Online webpage. 

A few years later I was in charge of the administration of the main game server and I had in my home computer a backup with 1 million game charfiles. A is a single game player stored as a regular file in the server filesystem, since the game server was (and it is still) using INI files to store each of the players information. It was impossible to open the charfiles folder with the Windows Explorer through Terminal Server, otherwise the machine would hang.

December 2001 has a very special place in Argentina history books. Between the 20 and 21 of December of 2001 there were riots on the (real world) streets, people died, and the President of Argentina had to resign from office, flying in a helicopter from the Casa Rosada (the office of the President of Argentina). Inside the game there were riots too, and players were protesting against the goverment while playing Argentum Online.

Time went by, and by the end of 2002 the development team of Noland Studios decided that the game was mostly finished. After fixing bugs and issues, in December 2002 the source code was released in the spirit of giving back to a community that made the game to grow, and for everyone to start its own game server. More details on the history of the game can be found at the "Brief history.txt" document available inside the Dec-2002 release package of the SourceForge project "MORGOAO", and at Argentum Online's webpage.

# The first years after December 2002

After the source code release, players began making contributions. Starting from the source code, small and medium tasks were being done by players, mostly inspired on already existing games, to solve concrete issues in their need, or just improve the game mechanics. Online games started to be available on the Internet at that time, and a popular one was Ultima Online, which when it hit the gaming market a few years back, it shown to be a huge improvement over existing games.

An online game is never short on features, and Argentum Online was the exception. One of the most annoying and missing features of the game was a way to trade game items between two players. The game provided no means to safely concrete such action, and back then players would need to throw each game item to the floor, throw the coins to the floor, and trust the game gods that the other party won't cheat, nor a third party would come to scene to steal what was lying on the floor.

My first contribution to the game was a system to safely trade between players game items for other goods or ingame coins. But again, no game is short on cheaters, specially on the Internet. As the argentinian saying goes, "made the law, found the loophole" ("hecha la ley hecha la trampa"), the trading system was not perfect and some initial bugs were found by players. 

If during the middle of the transaction one of the player's Internet connection went down, the other party would get the items and the original player won't lose the items he or she was trading, creating a way to duplicate game goods and breaking the game economy. It was a fun experience on the downsides and pitfalls of software engineering, and a hard-earned lesson on how software testing shall not be done, specially while being on the first year of my university studies.

By the end of 2004 my personal life was a mess, I was struggling to keep up with my university studies, and I had to abandon my tasks on the development and administration of the Argentum Online Official game server.

Many people contributed back then, and my memory does not serves me well to remember the many names of the many contributors to the game, not only on programming but also graphics, sounds, game design, etc. There is a list of names on today's Argentum Online website [AOSTAFF] which I'm told contains the historic names since the beginning.

# Source Code Migration

## Rewriting Software Projects

Many people argue that rewriting a software project from scratch is a bad idea. One of such arguments was done by Joel Spolsky, who today is known as the founder and CEO of the Stack Overflow network. In his essay "Things You Should Never Do, Part I", he claims that rewriting a software product from scratch is "the single worst strategic mistake that any software company can make". He further argues:

> The idea that new code is better than old is patently absurd. Old code has been used. It has been tested. Lots of bugs have been found, and they've been fixed. There's nothing wrong with it. It doesn't acquire bugs just by sitting around on your hard drive. Au contraire, baby! Is software supposed to be like an old Dodge Dart, that rusts just sitting in the garage? Is software like a teddy bear that's kind of gross if it's not made out of all new material?

I learned his advice the hard way: by not following it.

## Rewriting Argentum Online

It is my understanding that I am solely the single person who has attempted the most number of times to rewrite Argentum Online to a modern programming technology. 

The first attempt was called "SeDeArOn" (which means "Servidor De Argentum Online" in spanish and can be translated as "Argentum Online Server" in english). Its source code lies on some back-up CDs on my parent's house. It was a failure and concrete proof on how not to write a game server. It was written in C++ and had one thread for each client connection. 

At that time, my knowledge of C++ systems programming was poor and bad. I was just finishing high school and with some free time on my hands before starting my university classes, I took my (very low) C++ programming knowledge and created a simple project that was «class oriented programming», without any kind of design. By «class oriented» I mean that instead of having a global C function I'd use classes as containers of similar functions. C++ is an «object oriented» programming language and I was lacking OOP knowledge and training, specifically «object oriented polymorphism». I luckily abandoned its development before wasting too much time on it.

C++ is a very good programming language for some specific use cases. For example, applications where performance is a key feature and each line of code is reviewed and tested by many developers. But having scarce development resources like I had meant that the time and effort I'd need to put into it would be some orders of magnitude greater than keeping the original Visual Basic 6.0 source code. 

Not only runtime performance is important, but development performance from a human resources point of view is also a major factor to consider in any software engineering project. None of the existing developers had knowledge of C++ programming, which meant that I had to write the code on my own. On the other hand, Visual Basic is a very easy programming language to learn, and its Integrated Development Enviroment has many interesting tools like symbols back-referencing and online debugging, lowering the bar on the skills required to make a contribution in source code form. 

I believe today that such tools and high level programming languages are important assets to consider in a software engineering project. Many people, some of them who I call friends today, learned how to write computer programs with Argentum Online while having fun. Some of them wrote features for the game, some of us wrote bugs for the game, and some of them wrote cheats for the game, too. But we all learned and we all had fun.

The second design error I mentioned was threading. Having one thread for each TCP client connection would mean having 300-500 threads running simultaneously, and today it is very well know that such design is not scalable. Dan Kegel discusses this very issue on his "The C10k problem" essay, which is a very interesting read for developers wanting to write scalable networking code and handling tens of thousands of network connections on a single machine. He was also part of the comitee delegated to the design of the Java 1.4 NIO API.

Stubborn as I am, the second attempt was to build a C++ version of the game client, this time called AONX. I wanted to try something more ambitious: to create a multiplatform version of the game client that each player would run on his computer, where the game would work good enough on both low end computers and high end ones by having two rendering engines integrated. The first rendering engine was a 2D engine written in SDL, and the second was an OpenGL engine that would render the 2D game world with hardware acceleration and nice visual effects.

I got to the point of having a simple version of both backend rendering engines, and some kind of playability. The networking protocol was mostly missing and the sound effects too. I then realized that I'd be needing lots of help, and decided to accept code contributions to the game by publishing the source code on a public source code repository, and releasing all the code as Open Source GNU/GPL. Some people downloaded the game, compiled it on their machines, and after realizing the game was an early prototype they would delete the entire folder on their computers. 

There was only one person with lots of interest on the project, he used to be a player like me, and with some C++ skills he initially helped with the AONX development. However, after some months and after having some creativity differences, our ways departed and my motivation to keep developing AONX went down too.

The third attempt was the fruit of my boredom while moving and living alone in my apartment. It was a prototype to see how easy or hard would it be to have an Argentum Online game server written in Python. Runtime performance was not of interest to me, but just development effort on my side. After a few weeks of work I had some initial prototype of a game server where it was possible to walk on the game world.

For AONX I wrote a simple code generation tool to help with the custom Argentum Online networking protocol. The protocol suffered a major rewrite by one of the developers that remained in charge of the Official Argentum Online Visual Basic Project, moving away from an ASCII based protocol to a binary one, where each game command would be represented by a single byte.

The new networking protocol was simple enough to be described by a text file containing, one line at a time, the name of the command, the decimal value of the opcode, and the lists of arguments with its data type. The protocol description files can still be found on the SVN repository of the AONX project. For my new Python Server the code generation was in the order of tens of lines of code, which saved me the trouble of writing thousands of lines of boilerplate code to describe the networking protocol. It is available on the GitHub project.

Later on and closer to the year 2013 a new attempt was made, this time by one friend and me, who we both were sharing our relentless rejection towards still programming in Visual Basic 6.0 in the year 2013. I wrote some initial Java code with the idea to have a simple project where people could easily catch up with coding conventions and tools, making it very easy for others to help and contribute code and patches. The idea was nice and my friend was enthusiastic about the project, but our interest went off and the project died.

There were other attempts by other Argentum Online players to rewrite the game in a modern programming environment. To my knowledge, the first one was AOJava by Gorlok. Then AOXP, which was an ambitious Java project. A lot of people were actively involved in the project, and many of them were members of the Official Team of programmers of the original Argentum Online source code. Another one called Argentum Online C by Parra, created in the C programmming language, shares some aspects of the game but it also deviates from the original game design since is has 3D features.

## Migration is not rewriting

A few years ago, Joel Spolsky surprised us again with an interesting project they had on his company. They sell a web application software for project management, FogBugz, mostly focused on software engineering project. It is like a bug tracker with many more features. 

Joel and his team built the initial version in ASP and Visual Basic Script near the year 2000, and by the year 2003 they wanted to licence the software to non-Windows users running Apache servers with PHP on Linux. ASP and Visual Basic Script does not run on Linux. He had a choice, either rewrite the software entirely in PHP, or produce some kind of translator that given the FogBugz source code would output PHP source code. They decided to go for the second option, to write a translator. He published some articles about it on his personal website, and the name of this translator is Wasabi.

Microsoft decided to pull the plug on Visual Basic 6.0 to force programmers into their new .Net programming platform. We had no more excuses to keep using a deprecated and ancient technology for our game.

The idea of having a source code translator to a new and modern programming technology was very appealing to me, specially to migrate the source code of Argentum Online away from Visual Basic 6.0, but I was missing some Compilers theory and practice.

## My first Compiler

In my attempt to actually graduate from University, I had started a project with a university professor I used to work with. She is one of the two professors of my Data Structures and Algorithms, where in that course I was a TA and later a Lecturer. In my personal quest of learning about compilers, I had the idea to write a simple compiler to translate a Python program to a C++ equivalent. One of the few language contructs that we were not going to support was eval(), since C++ does not easily allow the implementation of eval() of a C++ program.

I was wrong about the "simple" part of compiler construction. In the end I had to abandon that project since it was taking me longer than expected, and a new opportunity to graduate and to write my Thesis came to light (In Argentina it is called «Tesina de Licenciatura en Informática» and the degree is a 5 years long bachelor. It is not a real European Master, but close). And while I never completed the Python to C++ compiler, I had managed to complete the Python parser. My «Pure Python Python Parser» is the fruit of this work, a Python program that parses Python source code and produce the syntax tree as its output.

I dedicated a period of almost two years over my weekends and free time to write the Python parser. At first I started throwing things to the wall to see what sticks, and in the end I took the "Grammar" file of the official Python implementation and wrote a tokenizer and a parser generator that outputs a recursive descent Python Parser in Python. For such big grammar, it was much easier to write a parser generator than a hand crafted parser. The generated Parser is 19700 lines of code.

In the process I learned that the CPython Grammar is not LL(1), contrary to the claims of the documentation. The reference implementation of the official CPython parser depends on the traversal of a non-deterministic graph, effectively implementing the parser with backtracking. LL(1) parsers shall not use backtracking.

## My second Translator

The distinction I like to make between a compiler and a translator is that every compiler is a translator, but not every translator is a compiler. I like to call a «Compiler» a program that given some well defined grammar in some BNF-equivalent form produces a tree as its output, and a translator to everything else. I don't know, however, if my definition is accurate enough on an academic level.

In the early weeks of 2014 I had an inspirational moment about how to write a Visual Basic parser. I already had my share of Compilers theory and practice with my First Compiler PPPP, and I realized that writing a BNF grammar and a tree walker just to translate one single program was overkill. I wanted to profit the most while having a low investment. Writing a BNF grammar, a parser, and a tree walker for the syntax tree is an error prone and tedious task. Even by using some of the existing parser generation tools, a grammar definition it is still needed.

I realized that Visual Basic 6.0 programs can be translated in the 95\% of the cases by just looking at the first few symbols of each line on a token level. There are no weird or nested expressions in the language, and by just writing a tokenizer that takes one line at a time, a parser can be built easily without the need to write a specialized BNF grammar. 

Furthermore, I was needing to write a translator for just one program, the Argentum Online server, and nothing else. 

It took me a few months in my spare time over the weekends to write an initial version, and doing so was a much more attractive activity than writing by hand code that was already written in another language. I decided for the translation to go from Visual Basic 6.0 to C++, since its the language I personally like the most.

Then, one day, I decided that the output of my translator was good enough to give it a shot through a C++ compiler. It took me a few weeks to realize my translation was full of bugs and after fixing lots of small translation issues, the code finally compiled with gcc. I estimate that it took me four weekends to fix the missing 5\% features of the translation by manually editing the C++ output of the translation.

It was done.

One interesting translation problem I did not see coming was the concatenation of strings with integers. In Visual Basic 6.0 there is an implicit data type coercion when appending an Integer to a String. Novice Visual Basic 6 programmers may remember that 2 + 2 may usually be "22", since sometimes in an expression one of the operands is a String and the language is implicitly converting the Integer to a String. I missed that detail on the translation program, and for every expression that was a concatenation of an inline String to an Integer the C++ compiler would treat it as an pointer addition to an int. For example, given the following program in Visual Basic 6.0:

    Dim A as String
    Dim X as Integer
    X = 2
    A = "Value" + X

it is translated to C++ as:

    std::string A;
    int X;
    X = 2;
    A = "Value" + X;

The Visual Basic version assigns the string Value2 to the A variable, while the C++ version assigns the string "lue" to the A variable, since in C++ an inline string is a const char* and adding an int to it means an array subscript. Equivalently:

    std::string A;
    int X;
    X = 2;
    A = "Value"[X];

or

    const char* tmp = "Value";
    std::string A;
    int X;
    X = 2;
    A = tmp[X];

At this moment I had already invested too much time and effort in manually fixing many translation problems, and going back and fixing my translator was not an option anymore. I would have lost all my manual changes. In the end, to fix this issue I wrote another translator, a C++ tokenizer which wraps every inline quoted string with an std::string constructor. Continuing with the example, my new translator would output the following code:

    std::string A;
    int X;
    A = std::string("Value") + X;

Which produces a compilation error every time there is an addition of a string to an int, making me happy to have an automatic way to detect 100\% of the cases of the issue.

Another key difference between Visual Basic and C++ is that in Visual Basic the logic, bitwise and boolean operators are syntactically written the same, but not in C++. Using the and operator on an Integer variable is a bitwise operation, like the & operator in C++. But using the and operator with boolean operands would result in a boolean operation, like the && operator in C++. However, my translator was not powerful enough to detect this semantic distinction between boolean and bitwise operations. The translation was on a token level, and to fix this problem a compiler capable of type inference was needed.

# A working server in Linux

After having a game server (barely) compiling I started removing and rewriting specific parts to accomodate to the new programming language. The first part I had to write was file I/O since my translation was missing those specific Visual Basic 6.0 constructs. File I/O in Visual Basic 6.0 is a syntactic feature, and the translator produced the original Visual Basic 6 code commented out.

The second piece that my game server was missing was networking and sockets. On the original Visual Basic 6.0 game server we were using Windows Sockets API, but luckily for us most of the sockets code was abstracted on global functions that would send data, receive data, close a socket, etc. The sockets code was originally written in 2003 by me, and now more than 10 years later I managed to modernize it. Yay!

I decided to use libevent as a sockets networking abstraction library, mostly because I already had some experience using it. I skipped boost::asio networking library because it may have some performance problems. Since it is advertised as a thread-safe library, boost::asio has an internal global mutex on each call of the system call epoll() that effectively kills performance processing lots of small messages.

But then again, performance at that level is not always critical and boost::asio has a major performance advantage on Windows machines since under the hood is using Completion Ports for networking, while libevent on Windows is still using select(). We're not using Windows for the server, though, so boost::asio is of no use to me.

The first running game server that actually worked was in a friend's laptop computer with a broken LCD screen that he had lying around inside his closet in his home. He installed Ubuntu Linux on it, gave me remote ssh access and we started using it for our initial tests and development. 

My friend was in charge of updating the game maps for a public release, and then he was (self) promoted to second in command. We met 12 years ago in the original game while he was the chief server administrator and project leader of the game, and here again we still are working on this very same project.

After that moment, other people and friends joined our development effort. Some of them we met 10-12 years ago, in the very game. We now have a webpage for Dakara Online with a forum where we want to form a community of players.

# Next steps

Dakara Online is a volunteer based project, where the effort and action only takes place on the weekends and free time during holidays. Today I am the only active software developer, and in the past I had help of a couple of friends on the C++ development effort. We are, however, a small team, and some of our own players are starting to offer help on various aspects of the development effort. For example we have two players that have been writing the game documentation on our wiki. 


[DAKARA] Dakara Online website - ( http://www.dakaraonline.org/ )

[DIC2001] December 2001 riots in Argentina - ( http://en.wikipedia.org/wiki/December_2001_riots_in_Argentina )

[AOVAULT] Argentum Online Vault - ( http://www.comunidadargentum.com/?page_id=176 )

[AOABOUT] About Argentum Online - ( http://www.comunidadargentum.com/?page_id=156 )

[AOSTAFF] Argentum Online Staff (Full historical list) - ( http://www.comunidadargentum.com/?page_id=18 )

[MORGOAO] SourceForge project where the original Argentum Online source code can be found - ( http://sourceforge.net/projects/morgoao/ )

[C10K] The C10K Problem - ( http://www.kegel.com/c10k.html )

[C10K2] JSR 51: New I/O APIs for the Java(TM) Platform - ( https://www.jcp.org/en/jsr/detail?id=51 )

[JOEL1] Things You Should Never Do, Part I - ( http://www.joelonsoftware.com/articles/fog0000000069.html )

[AONX] AONX - ( http://aonx.sourceforge.net/ )

[AOPYSERV] Argentum Python Server - ( https://github.com/alejolp/argentum-py-server )

[VB6EOL1] Microsoft Support Lifecycle: Visual Basic 6 - ( http://support.microsoft.com/lifecycle/search/?sort=PN&alpha=Visual+basic+6&Filter=FilterNO )

[VB6EOL2] Secure your Visual Basic 6.0 investment with Microsoft .NET - ( https://msdn.microsoft.com/en-gb/dd408373.aspx )

[AOJAVA] AOJava - ( http://sourceforge.net/projects/aojava/ )

[AOXP] AOXP - ( https://github.com/aoxp/AOXP-Server )

[AOCPARRA] Argentum Online C - ( http://dev.aoc.parrastudios.com/ )

[JOEL2] Language Wars - ( http://www.joelonsoftware.com/items/2006/09/01.html )

[JOEL3] Wasabi - ( http://www.joelonsoftware.com/items/2006/09/01b.html )

[CODINGH1] Has Joel Spolsky Jumped the Shark? - ( http://blog.codinghorror.com/has-joel-spolsky-jumped-the-shark/ )

[PPPP] Pure Python Python Parser - ( https://github.com/alejolp/pppp )

[CPPSTRFIX] tokenizerstring.py - ( https://gist.github.com/alejolp/3a700e1730e0328c68de )

[ASIOMUTEX] boost::asio multithreading performance - ( http://stackoverflow.com/a/1238315/209629 )

[WINCP] Windows Completion Ports - ( https://msdn.microsoft.com/en-us/library/aa365198(VS.85).aspx )



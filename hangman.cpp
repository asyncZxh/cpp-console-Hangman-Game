#include <iostream>
#include <ctime>
#include <string>
#include <chrono>
#include <thread>
#include <unistd.h>

char menu();
void option(std::string &, std::string &, int &, int &, int &, int &);
bool exit();
void difficulty(std::string &);
void category(std::string &);
void progress(int &, int &, int &, int &);
void hangman(int, std::string);
std::string guessLetter();
void initializeBlanks(std::string, std::string &, int);
bool checkLetter(std::string, std::string, int, std::string &);
void displayWord(std::string, int);
void displayHint(std::string[][30], int, std::string);
void displayLives(int);
bool checkString(std::string, std::string);
char playAgain();
void playing1(std::string[][30], std::string[][30], int, int, std::string, int, std::string, int, int, std::string, int &, int &, int &, int &);
void playing2(std::string[][30], std::string[][30], int, int, std::string, int, std::string, int, int, std::string, int &, int &, int &, int &);
void playing3(std::string[][30], std::string[][30], int, int, std::string, int, std::string, int, int, std::string, int &, int &, int &, int &);
void playing4(std::string[][30], std::string[][30], int, int, std::string, int, std::string, int, int, std::string, int &, int &, int &, int &);
void playing5(std::string[][30], std::string[][30], int, int, std::string, int, std::string, int, int, std::string, int &, int &, int &, int &);
int main()
{
    srand(time(NULL));
    std::string wordsTech[][30] = {{"programming", "javascript", "python", "internet", "compiler", "computer", "frameworks", "library", "error", "debug", "code", "logic", "syntax", "browser", "frontend", "backend", "software", "hardware", "application", "api", "css", "html", "laravel", "nodejs", "linux", "fullstack developer", "software engineer", "cybersecurity", "hacker", "operating system"},
                                   {"algorithm", "database", "firewall", "encryption", "processor", "cloud computing", "malware", "bandwidth", "bios", "server", "virtual reality", "blockchain", "cache", "open source", "ethernet", "quantum computing", "neural network", "machine learning", "robotics", "deep learning", "internet of things", "ui", "hacking", "data mining", "latency", "firmware", "augmented reality", "source code", "web crawler", "artificial intelligence"},
                                   {"asynchronous", "virtualization", "pseudocode", "distributed system", "microservices", "hypervisor", "refactoring", "containerization", "polymorphism", "scalability", "load balancing", "multithreading", "hashing", "cyber-physical system", "cryptanalysis", "deepfake", "homomorphic encryption", "zero trust architecture", "federated learning", "quantum supremacy", "convolutional network", "recursive function", "automata theory", "compiler optimization", "syntactic sugar", "edge computing", "parallel processing", "no sql", "data warehousing", "reverse engineering"}};

    std::string hintsTech[][30] = {{"building algorithms and logic to control computer behavior", "a languange for web development", "a popular and easy-to-read languange", "global network", "converts source code into machine code", "an electronic device that processes data", "pre-made tools for coding", "reusable code collection", "mistake in coding", "fixing code errors", "instructions for a program", "program reasoning", "rules for writing code", "use to visit website", "the visible part of a website", "handles website data and logic", "programs running on a computer", "the physical parts of a computer", "a software program", "lets programs talk to each other", "styles a webpage", "structures a webpage", "a php web framework", "runs javascript outside browsers", "a free and open-source operating system", "builds both frontend and backend", "designs and creates software", "protects data and systems", "someone who finds and exploits system weaknesses", "runs and manages a computer"},
                                   {"a step-by-step set of rules for solving a problem", "a structured way to store and manage data", "a security system that blocks unauthorized access", "the process of converting data into a secret code", "the brain of a computer that executes instructions", "storing data and applications on remote servers", "malicious software that can harm a system", "the amount of data that can be transmitted over a network", "the basic input/output system of a computer", "a computer that provides data to other computers", "a simulated experience in a digital environment", "a decentralized and secure digital ledger", "a temporary storage area for fast access to data", "software with publicly available code", "a wired network connection standard", "advanced computing using quantum mechanics", "a machine learning model inspired by the human brain", "a technology that enables computers to learn from data", "the science of designing and building robots", "a subset of ai that mimics the human brain's neural networks", "the connection of everyday devices to the internet", "the design of all visual elements that users interact within a digital product", "illegal activities done using computers or the internet", "extracting useful information from large datasets", "the rate at which data is processed or transmitted", "software embedded into hardware for basic functionality", "technology that overlays digital content in the real world", "the original human-readable code of a program", "a bot that scans and indexes websites for search engines", "technology that enables machines to simulate human intelligence"},
                                   {"executing code without waiting for previous tasks to finish", "creating multiple simulated environments on one physical machine", "a simplified version of code that represents an algorithm", "a system where multiple computers work together as one", "a software architecture style for developing modular applications", "software that manages virtual machines", "improving code without changing its functionality", "using lightweight, isolated environments for software deployment", "an oop concept where objects can take multiple forms", "the ability of a system to handle growing workload", "distributing network traffic to maintain system stability", "running multiple processes simultaneously within a program", "converting data into fixed-size values for security and indexing", "integrating digital and physical systems for real-time control", "the study of breaking cryptographic codes", "ai-generated media that replaces real images or videos", "a form of encryption that allows computations on encrypted data", "a security model requiring strict identity verification", "training machine learning models without sharing raw data", "the ability of quantum computers to outperform classical ones", "a type of neural network specialized in image recognition", "a function that calls itself within its definition", "the study of abstract machines and computational problems", "optimizing code translation to improve performance", "simplified syntax that makes programming easier", "processing data closer to the source rather than cloud servers", "executing multiple computations at the same time", "a non-relational database system", "a system for storing and analyzing large datasets", "analyzing and modifying software without original source code"}};

    std::string wordsAnimals[][30] = {{"cat", "dog", "lion", "tiger", "elephant", "giraffe", "rabbit", "fox", "bear", "panda", "zebra", "monkey", "horse", "kangaroo", "sheep", "cow", "goat", "pig", "deer", "frog", "duck", "owl", "eagle", "dolphin", "whale", "penguin", "turtle", "parrot", "hamster", "butterfly"},
                                      {"cheetah", "jaguar", "leopard", "wolf", "hyena", "bison", "chimpanzee", "gorilla", "meerkat", "koala", "platypus", "otter", "raccoon", "armadillo", "anteater", "porcupine", "skunk", "moose", "reindeer", "buffalo", "coyote", "lynx", "beaver", "badger", "wombat", "hedgehog", "ferret", "manatee", "narwhal", "cassowary"},
                                      {"axolotl", "blobfish", "pangolin", "fossa", "kakapo", "quokka", "aardvark", "numbat", "markhor", "saiga", "okapi", "shoebill", "dugongo", "basilisk", "olm", "echidna", "tenrec", "solenodon", "dhole", "serval", "caracal", "quoll", "takin", "vaquita", "hoatzin", "gila monster", "ibex", "binturong", "yeti crab", "harpy eagle"}};

    std::string hintsAnimals[][30] = {{"a small pet that loves to purr", "a loyal pet that barks", "the king of the jungle", "a big striped wild cat", "a giant animal with a trunk", "a tall animal with a long neck", "a small animal that hops", "a clever animal with a bushy tail", "a large furry animal found in forests", "a black and white bear that eats bamboo", "a horse-like animal with black and white stripes", "a playful animal that swings on trees", "a strong animal often used for riding", "an australian animal that jumps with a pouch", "a fluffy farm animal that gives wool", "a farm animal that gives milk", "a farm animal with horns", "a pink farm animal that oinks", "a graceful animal with antlers", "a small green animal that jumps", "a bird that quacks and swims", "a bird that is active at night", "a powerful bird with sharp eyes", "a smart and playful sea animal", "a giant sea animal that sings", "a black and white bird that cannot fly", "a slow-moving reptile with a shell", "a colorful bird that can talk", "a tiny pet rodent that loves to run on a wheel", "a beautiful insect with colorful wings"},
                                      {"the fastest land animal", "a spotted big cat found in rainforests", "a wild cat known for its rosette patterns", "a wild dog that hunts in packs", "a laughing scavenger", "a large wild ox with a hump", "a highly intelligent primate", "a powerful ape that lives in forests", "a small animal that stands on two legs", "an australian animal that eats eucalyptus", "a rare egg-laying mammal", "a playful water-loving mammal", "a nocturnal animal known for its masked face", "a mammal with a hard shell", "an animal with a long tongue that eats ants", "a rodent covered in sharp quills", "a small black and white animal that sprays a bad smell", "a large deer with broad antlers", "a deer species often linked to Christmas", "a large wild animal related to cows", "a wild canine found in North America", "a medium-sized wild cat with tufted ears", "a rodent that builds dams in rivers", "a burrowing mammal with black and white fur", "a stocky marsupial native to Australia", "a small spiky mammal that rolls into a ball", "a long, slender mammal kept as a pet", "a gentle sea mammal also called a 'sea cow'", "a whale with a long spiral tusk", "a large flightless bird known for its aggression"},
                                      {"a rare amphibian that can regenerate limbs", "a deep-sea fish with a gelatinous body", "a scaly mammal that rolls into a ball", "a cat-like predator found in Madagascar", "a large, flightless, nocturnal parrot", "a small, smiling marsupial from Australia", "a burrowing mammal that eats ants", "a striped anteater from Australia", "a wild goat with twisted horns", "an antelope with an unusual long nose", "a forest-dwelling relative of the giraffe", "a large bird with a beak shaped like a shoe", "a close relative of the manatee", "a lizard that can run on water", "a blind cave-dwelling salamander", "a spiny egg-laying mammal", "a small mammal with hedgehog-like features", "a venomous mammal with a long snout", "a wild dog known as the 'whistling dog'", "a spotted wild cat from Africa", "a wild cat with tufted ears and long legs", "a carnivorous marsupial from Australia", "a large goat-antelope from the Himalayas", "a critically endangered small porpoise", "a prehistoric-looking bird that smells bad", "a venomous lizard from North America", "a wild goat that lives on mountains", "a tree-dwelling mammal that smells like popcorn", "a crab covered in hairy, bacteria-filled filaments", "a powerful eagle with massive talons"}};

    std::string wordsMath[][30] = {{"addition", "subtraction", "multiplication", "division", "fraction", "decimal", "percentage", "equation", "variable", "algebra", "geometry", "circle", "triangle", "square", "rectangle", "radius", "diameter", "area", "perimeter", "volume", "angle", "parallel", "symmetry", "counting", "number", "average", "mean", "mode", "graph", "table"},
                                   {"exponent", "logarithm", "quadratic", "polynomial", "binomial", "trigonometry", "calculus", "integral", "derivative", "limit", "function", "coordinate", "vector", "matrix", "theorem", "postulate", "axiom", "inequality", "parabola", "hyperbola", "ellipse", "probability", "statistics", "permutation", "combination", "factorial", "sequence", "series", "congruence", "proof"},
                                   {"bijection", "homomorphism", "isomorphism", "eigenvalue", "eigenvector", "orthogonality", "determinant", "jacobian", "hessian", "manifold", "topology", "tensor", "group theory", "ring theory", "field theory", "graph theory", "measure theory", "set theory", "number theory", "game theory", "chaos theory", "cryptography", "laplacian", "fourier transform", "zeta function", "riemann hypothesis", "continuum hypothesis", "goldbach conjecture", "poincare conjecture", "turing machine"}};

    std::string hintsMath[][30] = {{"the process of combining two or more numbers", "taking one number away from another", "repeated addition of the same number", "splitting a number into equal parts", "a part of a whole represented with a numerator and denominator", "a number with a decimal point", "a way to express a number as a portion of 100", "a mathematical statement with an equal sign", "a letter that represents a number in math", "a branch of math dealing with symbols and equations", "the study of shapes, sizes, and angles", "a round shape with no corners", "a shape with three sides", "a four-sided shape with equal sides", "a four-sided shape with opposite sides equal", "the distance from the center of a circle to its edge", "the longest distance across a circle passing through the center", "the amount of space inside a shape", "the distance around a shape", "the amount of space an object occupies", "the space between two intersecting lines", "two lines that never meet", "a balanced and identical shape on both sides", "the act of determining the number of objects", "a mathematical value used for counting and calculations", "the sum of numbers divided by the count of numbers", "the middle number in a set of numbers", "the most frequently occurring number in a set", "a visual representation of data", "an organized display of numbers or information"},
                                   {"a number that represents repeated multiplication", "the inverse operation of exponentiation", "an equation where the highest exponent is 2", "an algebraic expression with multiple terms", "an algebraic expression with exactly two terms", "the study of angles and their relationships", "a branch of math dealing with change and motion", "the process of finding the area under a curve", "the rate of change of a function", "the value a function approaches", "a relation between inputs and outputs", "a pair of numbers that define a position in a plane", "a quantity with both magnitude and direction", "a rectangular array of numbers", "a mathematical statement that can be proven", "a statement assumed true without proof", "a fundamental truth used as a basis for reasoning", "a mathematical comparison using <, >, or =", "a symmetric curve formed by a quadratic equation", "an open curve with two branches", "an oval-shaped curve", "the likelihood of an event occurring", "the study of data collection and analysis", "an arrangement of objects in a specific order", "a selection of objects without considering order", "the product of all positive integers up to a number", "an ordered list of numbers following a pattern", "the sum of terms in a sequence", "when two shapes are identical in shape and size", "a logical argument that verifies a mathematical statement"},
                                   {"a function that is both one-to-one and onto", "a structure-preserving map between algebraic structures", "a mapping that preserves both operation and structure", "a scalar associated with a linear transformation", "a vector whose direction remains unchanged by a transformation", "the concept of perpendicularity in vector spaces", "a scalar value that represents certain properties of a matrix", "a matrix of first-order partial derivatives", "a square matrix of second-order partial derivatives", "a topological space that locally resembles Euclidean space", "the study of properties preserved through deformations", "a mathematical object describing multi-dimensional relations", "the study of algebraic structures called groups", "the study of sets equipped with two binary operations", "the study of algebraic structures that generalize fields", "the study of graphs and their applications", "a branch of mathematics dealing with measures and integration", "the study of collections of objects", "the study of properties of integers", "the study of mathematical models of strategic interactions", "the study of unpredictable and complex dynamic systems", "the practice of securing communication using mathematical techniques", "a differential operator in vector calculus", "a mathematical transformation used for signal processing", "a special function that encodes number theory properties", "one of the most famous unsolved problems in mathematics", "a hypothesis about the structure of infinite sets", "a famous unproven conjecture about prime numbers", "a solved conjecture related to topology and geometry", "a theoretical model of computation"}};

    std::string wordsHumanBody[][30] = {{"heart", "brain", "lungs", "skin", "bones", "muscle", "blood", "stomach", "liver", "kidney", "eye", "ear", "nose", "mouth", "teeth", "tongue", "hair", "nail", "vein", "artery", "rib", "skull", "spine", "joint", "hand", "foot", "finger", "toe", "elbow", "knee"},
                                        {"pancreas", "intestine", "esophagus", "diaphragm", "cartilage", "ligament", "tendon", "plasma", "neuron", "synapse", "hormone", "pituitary", "thyroid", "adrenal", "spleen", "lymph", "cornea", "retina", "cochlea", "eardrum", "pharynx", "larynx", "trachea", "bronchi", "alveoli", "aorta", "capillary", "atrium", "ventricle", "metacarpal"},
                                        {"hypothalamus", "medulla", "cerebellum", "meninges", "axons", "dendrites", "myelin", "epithelium", "endothelium", "pericardium", "pleura", "peritoneum", "synovium", "chondrocytes", "osteocytes", "erythrocytes", "leukocytes", "thrombocytes", "hemoglobin", "melanin", "keratin", "sebaceous", "sudoriferous", "lacrimal", "olfactory", "vestibular", "cochlear", "saccule", "utricle", "fovea"}};

    std::string hintsHumanBody[][30] = {{"pumps blood throughout the body", "controls thoughts and movements", "helps with breathing", "largest organ of the body", "supports the body and protects organs", "allows movement by contracting", "carries oxygen and nutrients", "digests food", "filters toxins from the blood", "removes waste from the blood", "organ for vision", "organ for hearing", "helps with smelling", "used for eating and speaking", "hard structures in the mouth for chewing", "muscle in the mouth for tasting", "grows on the head", "protects fingertips and toes", "carries blood to the heart", "carries blood away from the heart", "protects the chest cavity", "protects the brain", "supports the body and helps with posture", "connects bones together", "used for grasping and holding", "supports walking and standing", "small part of the hand", "small part of the foot", "joint that bends the arm", "joint that bends the leg"},
                                        {"produces insulin and digestive enzymes", "absorbs nutrients from food", "connects the throat to the stomach", "muscle that helps with breathing", "flexible tissue that cushions joints", "connects bones and stabilizes joints", "connects muscles to bones", "the liquid component of blood", "nerve cell that transmits signals", "a connection point between neurons", "chemical messenger in the body", "gland that regulates growth and hormones", "gland that controls metabolism", "gland that produces stress hormones", "organ that filters blood and fights infections", "fluid that helps fight infections", "transparent layer covering the eye", "part of the eye that detects light", "spiral-shaped organ for hearing", "thin membrane that vibrates with sound", "throat passage for food and air", "voice box that produces sound", "windpipe that carries air to the lungs", "airway branches leading to lungs", "tiny sacs for gas exchange in lungs", "largest artery carrying blood from the heart", "smallest blood vessels", "upper chamber of the heart", "lower chamber of the heart", "bones in the hand"},
                                        {"regulates body temperature and emotions", "controls involuntary functions like breathing", "coordinates movement and balance", "protective membranes surrounding the brain", "nerve fibers that transmit signals", "receive signals in nerve cells", "insulating layer around nerves", "protective tissue covering body surfaces", "tissue lining blood vessels", "membrane surrounding the heart", "membrane covering the lungs", "membrane lining the abdominal cavity", "lubricating membrane in joints", "cells that produce cartilage", "bone-forming cells", "red blood cells carrying oxygen", "white blood cells fighting infections", "platelets that help with clotting", "protein in blood carrying oxygen", "pigment that determines skin color", "protein in hair and nails", "glands producing skin oil", "glands that produce sweat", "gland that produces tears", "responsible for the sense of smell", "helps maintain balance and spatial orientation", "transmits sound information to the brain", "detects vertical head movement", "detects horizontal head movement", "area of the retina for sharp vision"}};

    std::string wordsHistory[][30] = {{"egypt", "rome", "greece", "china", "mesopotamia", "renaissance", "pyramids", "hieroglyphs", "pharaoh", "gladiator", "colosseum", "spartans", "olympics", "dynasty", "great wall", "samurai", "medieval", "knight", "castle", "vikings", "explorer", "compass", "columbus", "revolution", "war", "treaty", "constitution", "president", "independence", "empire"},
                                      {"persian empire", "hammurabi", "hieroglyphics", "alexander", "genghis khan", "napoleon", "vikings", "crusades", "renaissance", "magna carta", "black death", "reformation", "ottoman empire", "industrial revolution", "cold war", "civil rights", "holocaust", "world war", "battle of hastings", "american revolution", "french revolution", "napoleonic wars", "roman republic", "ancient greece", "trojan war", "great depression", "apollo 11", "berlin wall", "moon landing", "pearl harbor"},
                                      {"byzantine empire", "carthaginian wars", "holy roman empire", "battle of thermopylae", "sumerians", "hittites", "peloponnesian war", "council of nicea", "treaty of westphalia", "congress of vienna", "meiji restoration", "russo-japanese war", "gutenberg press", "tang dynasty", "hanseatic league", "teutonic knights", "battle of lepanto", "boer war", "pragmatic sanction", "edicts of ashoka", "hundred years' war", "battle of austerlitz", "defenestration of prague", "rosetta stone", "wars of the roses", "zulu kingdom", "treaty of tordesillas", "janissaries", "taiping rebellion", "spanish armada"}};

    std::string hintsHistory[][30] = {{"ancient civilization along the nile river", "powerful empire in europe", "birthplace of democracy and philosophy", "one of the oldest civilizations", "ancient region between tigris and euphrates", "period of great cultural rebirth", "massive tombs built by egyptians", "ancient writing system of egypt", "egyptian ruler", "fighter in roman arenas", "famous roman amphitheater", "elite warriors of ancient greece", "sporting event that began in greece", "a ruling family of an empire", "long wall built to protect china", "japanese warrior class", "period of castles and knights", "armored soldier of the middle ages", "fortified home of kings and nobles", "seafaring raiders from scandinavia", "person who travels to discover new lands", "navigation tool for direction", "explorer who reached the americas", "major political and social upheaval", "armed conflict between nations", "official agreement between countries", "set of laws governing a country", "elected leader of a country", "freedom from colonial rule", "large territory ruled by an emperor"},
                                      {"powerful ancient empire in the middle east", "babylonian king who created one of the first legal codes", "ancient egyptian picture writing system", "conqueror who spread greek culture", "mongol leader who created a vast empire", "french military leader and emperor", "norse seafarers known for raiding and exploring", "religious wars between christians and muslims", "cultural movement that revived art and learning", "english document limiting the king’s power", "deadly pandemic in medieval europe", "religious movement that led to the rise of protestantism", "powerful empire centered in turkey", "period of major technological and industrial advances", "political tension between usa and ussr", "struggle for racial equality in the usa", "genocide of jewish people during wwii", "global conflicts involving multiple nations", "battle that changed english history in 1066", "war that led to america's independence", "uprising that overthrew the french monarchy", "series of wars led by napoleon bonaparte", "government before the roman empire", "birthplace of democracy and philosophy", "legendary war between greeks and trojans", "economic crisis of the 1930s", "first manned moon landing mission", "barrier dividing east and west berlin", "historic event where humans walked on the moon", "japanese attack that led the usa into wwii"},
                                      {"eastern roman empire that lasted until 1453", "series of wars between rome and carthage", "medieval empire that claimed to be the successor of rome", "famous battle where 300 spartans fought persians", "one of the first civilizations in mesopotamia", "ancient anatolian civilization known for ironwork", "war between athens and sparta in ancient greece", "early christian council that established doctrine", "treaty that ended the thirty years' war", "meeting that redrew europe after napoleon’s defeat", "japanese political revolution that modernized the country", "war between russia and japan in 1904-1905", "printing invention that revolutionized communication", "golden age dynasty of china", "medieval trade alliance in northern europe", "germanic crusading knights", "naval battle that ended ottoman expansion in the mediterranean", "conflict between britain and dutch settlers in south africa", "law ensuring habsburg succession in austria", "edict by an indian emperor promoting buddhism", "long conflict between england and france", "napoleon’s greatest battlefield victory", "incident that sparked the thirty years' war", "artifact that helped decipher egyptian writing", "civil war in england between rival royal houses", "powerful african kingdom known for its warriors", "agreement dividing the new world between spain and portugal", "elite ottoman soldiers taken as children", "massive 19th-century rebellion in china", "failed naval invasion of england by spain in 1588"}};

    int numberOfWords = sizeof(wordsTech[0]) / sizeof(wordsTech[0][0]);
    int randomize;
    std::string selectedWord;
    int sizeOfSelectedWord;
    std::string blanks;
    int lives;
    int hangmanCondition;
    char choose;
    std::string level = "normal";
    std::string type = "technology";
    int totalWins = 0;
    int totalLose = 0;
    int totalCorrectGuess = 0;
    int totalWrongGuess = 0;
    char exitGame = false;
    do
    {
        choose = menu();
        switch (choose)
        {
        case '1':
            if (type == "technology")
            {
                playing1(wordsTech, hintsTech, numberOfWords, randomize, selectedWord, sizeOfSelectedWord, blanks, lives, hangmanCondition, level, totalWins, totalLose, totalCorrectGuess, totalWrongGuess);
            }
            else if (type == "animals")
            {
                playing2(wordsAnimals, hintsAnimals, numberOfWords, randomize, selectedWord, sizeOfSelectedWord, blanks, lives, hangmanCondition, level, totalWins, totalLose, totalCorrectGuess, totalWrongGuess);
            }
            else if (type == "mathematics")
            {
                playing3(wordsMath, hintsMath, numberOfWords, randomize, selectedWord, sizeOfSelectedWord, blanks, lives, hangmanCondition, level, totalWins, totalLose, totalCorrectGuess, totalWrongGuess);
            }
            else if (type == "human body")
            {
                playing4(wordsHumanBody, hintsHumanBody, numberOfWords, randomize, selectedWord, sizeOfSelectedWord, blanks, lives, hangmanCondition, level, totalWins, totalLose, totalCorrectGuess, totalWrongGuess);
            }
            else if (type == "history")
            {
                playing5(wordsHistory, hintsHistory, numberOfWords, randomize, selectedWord, sizeOfSelectedWord, blanks, lives, hangmanCondition, level, totalWins, totalLose, totalCorrectGuess, totalWrongGuess);
            }
            break;
        case '2':
            option(level, type, totalWins, totalLose, totalCorrectGuess, totalWrongGuess);
            break;
        case '3':
            exitGame = exit();
            break;
        }
    } while (exitGame == false);
    return 0;
}
char menu()
{
    std::string choose;
    std::cout << "[HANGMAN GAME]\n\n";
    std::cout << "[1]START\n";
    std::cout << "[2]OPTION\n";
    std::cout << "[3]EXIT\n";
    std::cout << ">> ";
    std::cin >> choose;
    while ((choose != "1" && choose != "2" && choose != "3") || choose.length() > 1)
    {
        std::cout << "(enter 1 to 3)\n";
        std::cout << ">> ";
        std::cin >> choose;
    }
    return choose[0];
}
void option(std::string &level, std::string &type, int &totalWins, int &totalLose, int &totalCorrectGuess, int &totalWrongGuess)
{
    std::string choice;
    char choice2;
    bool running = true;
    while (running)
    {
        std::cout << std::endl;
        std::cout << "[1]DIFFICULTY(" << level << ")\n";
        std::cout << "[2]CATEGORY(" << type << ")\n";
        std::cout << "[3]PROGRESS(view progress)\n";
        std::cout << "[0]exit\n";
        std::cout << ">> ";
        std::cin >> choice;
        std::cout << std::endl;
        while ((choice != "1" && choice != "2" && choice != "3" && choice != "0") || choice.size() > 1)
        {
            std::cout << "(enter from 1-3 or 0)\n";
            std::cin >> choice;
        }
        choice2 = choice[0];
        switch (choice2)
        {
        case '1':
            difficulty(level);
            break;
        case '2':
            category(type);
            break;
        case '3':
            progress(totalWins, totalLose, totalCorrectGuess, totalWrongGuess);
            break;
        case '0':
            running = false;
            break;
        }
    }
}
bool exit()
{
    return true;
}
void difficulty(std::string &level)
{
    std::string currentDifficulty = level;
    std::string input;
    bool running = true;
    char choice;
    std::cout << std::endl;
    while (running)
    {
        std::cout << "[1]Easy\n";
        std::cout << "[2]Normal\n";
        std::cout << "[3]Hard(additional 5 lives)\n";
        std::cout << "[0]exit\n";
        std::cout << ">> ";
        std::cin >> input;
        std::cout << std::endl;
        while ((input != "1" && input != "2" && input != "3" && input != "0") || input.size() > 1)
        {
            std::cout << "(enter from 1-3 or 0)\n";
            std::cin >> input;
        }
        choice = input[0];
        switch (choice)
        {
        case '1':
            if (currentDifficulty != "easy")
            {
                level = "easy";
                currentDifficulty = level;
                for (int i = 1; i <= 3; i++)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    std::cout << ".";
                    if (i == 3)
                    {
                        sleep(1);
                        std::cout << "difficulty updated!";
                        sleep(1);
                        std::cout << "\n\n\n";
                    }
                }
            }
            else
            {
                std::cout << "current difficulty is set to " << level;
                sleep(2);
                std::cout << "\n\n\n";
            }
            break;
        case '2':
            if (currentDifficulty != "normal")
            {
                level = "normal";
                currentDifficulty = level;
                for (int i = 1; i <= 3; i++)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    std::cout << ".";
                    if (i == 3)
                    {
                        sleep(1);
                        std::cout << "difficulty updated!";
                        sleep(1);
                        std::cout << "\n\n\n";
                    }
                }
            }
            else
            {
                std::cout << "current difficulty is set to " << currentDifficulty;
                sleep(2);
                std::cout << "\n\n\n";
            }
            break;
        case '3':
            if (currentDifficulty != "hard")
            {
                level = "hard";
                currentDifficulty = level;
                for (int i = 1; i <= 3; i++)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    std::cout << ".";
                    if (i == 3)
                    {
                        sleep(1);
                        std::cout << "difficulty updated!";
                        sleep(1);
                        std::cout << "\n\n\n";
                    }
                }
            }
            else
            {
                std::cout << "current difficulty is set to " << currentDifficulty;
                sleep(2);
                std::cout << "\n\n\n";
            }
            break;
        case '0':
            running = false;
            break;
        }
    }
}
void category(std::string &type)
{
    std::string currentCategory = type;
    std::string input;
    bool running = true;
    char choice;
    std::cout << std::endl;
    while (running)
    {
        std::cout << "[1]Technology\n";
        std::cout << "[2]Animals\n";
        std::cout << "[3]Mathematics\n";
        std::cout << "[4]Human Body\n";
        std::cout << "[5]History\n";
        std::cout << "[0]exit\n";
        std::cout << ">> ";
        std::cin >> input;
        std::cout << std::endl;
        while (((input < "1" || input > "5") && input != "0") || input.size() > 1)
        {
            std::cout << "(enter from 1-5 or 0)\n";
            std::cin >> input;
        }
        choice = input[0];
        switch (choice)
        {
        case '1':
            if (currentCategory != "technology")
            {
                type = "technology";
                currentCategory = type;
                for (int i = 1; i <= 3; i++)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    std::cout << ".";
                    if (i == 3)
                    {
                        sleep(1);
                        std::cout << "category updated!";
                        sleep(1);
                        std::cout << "\n\n\n";
                    }
                }
            }
            else
            {
                std::cout << "current category is set to " << currentCategory;
                sleep(2);
                std::cout << "\n\n\n";
            }
            break;
        case '2':
            if (currentCategory != "animals")
            {
                type = "animals";
                currentCategory = type;
                for (int i = 1; i <= 3; i++)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    std::cout << ".";
                    if (i == 3)
                    {
                        sleep(1);
                        std::cout << "category updated!";
                        sleep(1);
                        std::cout << "\n\n\n";
                    }
                }
            }
            else
            {
                std::cout << "current category is set to " << currentCategory;
                sleep(2);
                std::cout << "\n\n\n";
            }
            break;
        case '3':
            if (currentCategory != "mathematics")
            {
                type = "mathematics";
                currentCategory = type;
                for (int i = 1; i <= 3; i++)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    std::cout << ".";
                    if (i == 3)
                    {
                        sleep(1);
                        std::cout << "category updated!";
                        sleep(1);
                        std::cout << "\n\n\n";
                    }
                }
            }
            else
            {
                std::cout << "current category is set to " << currentCategory;
                sleep(2);
                std::cout << "\n\n\n";
            }
            break;
        case '4':
            if (currentCategory != "human body")
            {
                type = "human body";
                currentCategory = type;
                for (int i = 1; i <= 3; i++)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    std::cout << ".";
                    if (i == 3)
                    {
                        sleep(1);
                        std::cout << "category updated!";
                        sleep(1);
                        std::cout << "\n\n\n";
                    }
                }
            }
            else
            {
                std::cout << "current category is set to " << currentCategory;
                sleep(2);
                std::cout << "\n\n\n";
            }
            break;
        case '5':
            if (currentCategory != "history")
            {
                type = "history";
                currentCategory = type;
                for (int i = 1; i <= 3; i++)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    std::cout << ".";
                    if (i == 3)
                    {
                        sleep(1);
                        std::cout << "category updated!";
                        sleep(1);
                        std::cout << "\n\n\n";
                    }
                }
            }
            else
            {
                std::cout << "current category is set to " << currentCategory;
                sleep(2);
                std::cout << "\n\n\n";
            }
            break;
        case '0':
            running = false;
            break;
        }
    }
}
void progress(int &totalWins, int &totalLose, int &totalCorrectGuess, int &totalWrongGuess)
{
    std::string exit;
    std::cout << "Total Wins: " << totalWins << std::endl;
    std::cout << "Total Lose: " << totalLose << std::endl;
    std::cout << "Total Correct Guess: " << totalCorrectGuess << std::endl;
    std::cout << "Total Wrong Guess: " << totalWrongGuess << std::endl;
    std::cout << "[0]exit\n";
    std::cout << ">> ";
    std::cin >> exit;
    while (exit != "0" || exit.size() > 1)
    {
        std::cout << "(enter from 0 to exit)\n";
        std::cin >> exit;
    }
}
void hangman(int hangmanCondition, std::string level)
{
    if (level == "easy" || level == "normal")
    {
        switch (hangmanCondition)
        {
        case 1:
            std::cout << " O\n";
            std::cout << "/|\\\n";
            std::cout << "/ \\\n\n";
            break;
        case 2:
            std::cout << " O\n";
            std::cout << "/|\\\n";
            std::cout << "/ \\    ||\n\n";
            break;
        case 3:
            std::cout << " O\n";
            std::cout << "/|\\    ||\n";
            std::cout << "/ \\    ||\n\n";
            break;
        case 4:
            std::cout << " O     ||\n";
            std::cout << "/|\\    ||\n";
            std::cout << "/ \\    ||\n\n";
            break;
        case 5:
            std::cout << "      \\\\\n";
            std::cout << "       00\n";
            std::cout << " O     ||\n";
            std::cout << "/|\\    ||\n";
            std::cout << "/ \\    ||\n\n";
            break;
        case 6:
            std::cout << " o---\\\\\n";
            std::cout << "      \\\\\n";
            std::cout << "       00\n";
            std::cout << " O     ||\n";
            std::cout << "/|\\    ||\n";
            std::cout << "/ \\    ||\n\n";
            break;
        case 7:
            std::cout << " o---\\\\\n";
            std::cout << " |    \\\\\n";
            std::cout << "       00\n";
            std::cout << " O     ||\n";
            std::cout << "/|\\    ||\n";
            std::cout << "/ \\    ||\n\n";
            break;
        case 8:
            std::cout << " o---\\\\\n";
            std::cout << " |    \\\\\n";
            std::cout << " |     00\n";
            std::cout << " O     ||\n";
            std::cout << "/|\\    ||\n";
            std::cout << "/ \\    ||\n\n";
        }
    }
    else
    {
        switch (hangmanCondition)
        {
        case 1:
            std::cout << " O\n";
            std::cout << "/|\\\n";
            std::cout << "/ \\\n\n";
            break;
        case 2:
            std::cout << " O\n";
            std::cout << "/|\\\n";
            std::cout << "/ \\    ||\n\n";
            break;
        case 3:
            std::cout << " O\n";
            std::cout << "/|\\    ||\n";
            std::cout << "/ \\    ||\n\n";
            break;
        case 4:
            std::cout << " O     ||\n";
            std::cout << "/|\\    ||\n";
            std::cout << "/ \\    ||\n\n";
            break;
        case 5:
            std::cout << "       00\n";
            std::cout << " O     ||\n";
            std::cout << "/|\\    ||\n";
            std::cout << "/ \\    ||\n\n";
            break;
        case 6:
            std::cout << "      \\\\\n";
            std::cout << "       00\n";
            std::cout << " O     ||\n";
            std::cout << "/|\\    ||\n";
            std::cout << "/ \\    ||\n\n";
            break;
        case 7:
            std::cout << "     \\\\\n";
            std::cout << "      \\\\\n";
            std::cout << "       00\n";
            std::cout << " O     ||\n";
            std::cout << "/|\\    ||\n";
            std::cout << "/ \\    ||\n\n";
            break;
        case 8:
            std::cout << "    -\\\\\n";
            std::cout << "      \\\\\n";
            std::cout << "       00\n";
            std::cout << " O     ||\n";
            std::cout << "/|\\    ||\n";
            std::cout << "/ \\    ||\n\n";
            break;
        case 9:
            std::cout << "   --\\\\\n";
            std::cout << "      \\\\\n";
            std::cout << "       00\n";
            std::cout << " O     ||\n";
            std::cout << "/|\\    ||\n";
            std::cout << "/ \\    ||\n\n";
            break;
        case 10:
            std::cout << " o---\\\\\n";
            std::cout << "      \\\\\n";
            std::cout << "       00\n";
            std::cout << " O     ||\n";
            std::cout << "/|\\    ||\n";
            std::cout << "/ \\    ||\n\n";
            break;
        case 11:
            std::cout << " o---\\\\\n";
            std::cout << " |    \\\\\n";
            std::cout << "       00\n";
            std::cout << " O     ||\n";
            std::cout << "/|\\    ||\n";
            std::cout << "/ \\    ||\n\n";
            break;
        case 12:
            std::cout << " o---\\\\\n";
            std::cout << " |    \\\\\n";
            std::cout << " |     00\n";
            std::cout << " O     ||\n";
            std::cout << "/|\\    ||\n";
            std::cout << "/ \\    ||\n\n";
            break;
        }
    }
}
std::string guessLetter()
{
    std::string guess;
    do
    {
        std::cout << "Guess letter: ";
        std::cin >> guess;
        if (guess.length() > 1)
        {
            std::cout << "(enter a single letter)\n";
        }
    } while (guess.length() > 1);
    guess = std::tolower(guess[0]);
    return guess;
}
void initializeBlanks(std::string selectedWord, std::string &blanks, int sizeOfSelectedWord)
{
    for (int i = 0; i < sizeOfSelectedWord; i++)
    {
        if (selectedWord[i] == ' ')
        {
            continue;
        }
        blanks[i] = '_';
    }
    std::cout << "\n\n";
}
bool checkLetter(std::string letter, std::string selectedWord, int sizeOfSelectedWord, std::string &blanks)
{
    for (int i = 0; i < sizeOfSelectedWord; i++)
    {
        if (blanks[i] == selectedWord[i])
        {
            continue;
        }
        if (selectedWord[i] == letter[0])
        {
            blanks[i] = letter[0];
            std::cout << "\n\n";
            return true;
        }
    }
    std::cout << "\n\n";
    return false;
}
void displayWord(std::string blanks, int sizeOfSelectedWord)
{
    std::cout << "Word: ";
    for (int i = 0; i < sizeOfSelectedWord; i++)
    {
        std::cout << blanks[i] << " ";
    }
    std::cout << "\n\n";
}
void displayHint(std::string hints[][30], int randomize, std::string level)
{
    if (level == "easy")
    {
        std::cout << "Hint: " << hints[0][randomize] << "\n\n\n";
    }
    else if (level == "normal")
    {
        std::cout << "Hint: " << hints[1][randomize] << "\n\n\n";
    }
    else if (level == "hard")
    {
        std::cout << "Hint: " << hints[2][randomize] << "\n\n\n";
    }
}
void displayLives(int lives)
{
    std::cout << "Lives: " << lives << "\n";
}
bool checkString(std::string selectedWord, std::string blanks)
{
    if (selectedWord == blanks)
    {
        std::cout << "You saved the man!\n";
        return false;
    }
    return true;
}
char playAgain()
{
    std::string play;
    std::cout << "\n";
    std::cout << "Play again?(Y/N): ";
    std::cin >> play;
    play[0] = std::toupper(play[0]);
    while ((play != "Y" && play != "N") || play.length() > 1)
    {
        std::cout << "(press y or n)\n";
        std::cout << "Play again?(Y/N): ";
        std::cin >> play;
        play[0] = std::toupper(play[0]);
    }
    std::cout << std::endl;
    return play[0];
}
void playing1(std::string wordsTech[][30], std::string hintsTech[][30], int numberOfWords, int randomize, std::string selectedWord, int sizeOfSelectedWord, std::string blanks, int lives, int hangmanCondition, std::string level, int &totalWins, int &totalLose, int &totalCorrectGuess, int &totalWrongGuess)
{
    srand(time(NULL));
    bool running;
    char play;
    do
    {
        for (int i = 1; i <= 3; i++)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::cout << ".";
            if (i == 3)
            {
                sleep(1);
            }
        }
        randomize = rand() % numberOfWords;
        if (level == "easy")
        {
            selectedWord = wordsTech[0][randomize];
            lives = 7;
        }
        else if (level == "normal")
        {
            selectedWord = wordsTech[1][randomize];
            lives = 7;
        }
        else if (level == "hard")
        {
            selectedWord = wordsTech[2][randomize];
            lives = 12;
        }
        sizeOfSelectedWord = selectedWord.length();
        blanks = selectedWord;
        hangmanCondition = 1;
        running = true;
        std::string letter;

        initializeBlanks(selectedWord, blanks, sizeOfSelectedWord);
        while (running)
        {
            hangman(hangmanCondition, level);
            displayWord(blanks, sizeOfSelectedWord);
            if (!checkString(selectedWord, blanks))
            {
                totalWins++;
                break;
            }
            displayLives(lives);
            displayHint(hintsTech, randomize, level);
            letter = guessLetter();
            if (checkLetter(letter, selectedWord, sizeOfSelectedWord, blanks))
            {
                totalCorrectGuess++;
                continue;
            }
            else
            {
                lives--;
                hangmanCondition++;
                totalWrongGuess++;
                if (level == "easy" || level == "normal")
                {
                    if (hangmanCondition == 8)
                    {
                        totalLose++;
                        hangman(hangmanCondition, level);
                        std::cout << "Failed\n";
                        running = false;
                        break;
                    }
                }
                else if (level == "hard")
                {
                    if (hangmanCondition == 12)
                    {
                        totalLose++;
                        hangman(hangmanCondition, level);
                        std::cout << "Failed\n";
                        running = false;
                        break;
                    }
                }
            }
        }
        play = playAgain();
        if (play == 'Y')
        {
            hangmanCondition = 1;
            running = true;
        }
        else
        {
            break;
        }
    } while (play == 'Y');
}
void playing2(std::string wordsAnimals[][30], std::string hintsAnimals[][30], int numberOfWords, int randomize, std::string selectedWord, int sizeOfSelectedWord, std::string blanks, int lives, int hangmanCondition, std::string level, int &totalWins, int &totalLose, int &totalCorrectGuess, int &totalWrongGuess)
{
    srand(time(NULL));
    bool running;
    char play;
    do
    {
        for (int i = 1; i <= 3; i++)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::cout << ".";
            if (i == 3)
            {
                sleep(1);
            }
        }
        randomize = rand() % numberOfWords;
        if (level == "easy")
        {
            selectedWord = wordsAnimals[0][randomize];
            lives = 7;
        }
        else if (level == "normal")
        {
            selectedWord = wordsAnimals[1][randomize];
            lives = 7;
        }
        else if (level == "hard")
        {
            selectedWord = wordsAnimals[2][randomize];
            lives = 12;
        }
        sizeOfSelectedWord = selectedWord.length();
        blanks = selectedWord;
        hangmanCondition = 1;
        running = true;
        std::string letter;

        initializeBlanks(selectedWord, blanks, sizeOfSelectedWord);
        while (running)
        {
            hangman(hangmanCondition, level);
            displayWord(blanks, sizeOfSelectedWord);
            if (!checkString(selectedWord, blanks))
            {
                totalWins++;
                break;
            }
            displayLives(lives);
            displayHint(hintsAnimals, randomize, level);
            letter = guessLetter();
            if (checkLetter(letter, selectedWord, sizeOfSelectedWord, blanks))
            {
                totalCorrectGuess++;
                continue;
            }
            else
            {
                lives--;
                hangmanCondition++;
                totalWrongGuess++;
                if (level == "easy" || level == "normal")
                {
                    if (hangmanCondition == 8)
                    {
                        totalLose++;
                        hangman(hangmanCondition, level);
                        std::cout << "Failed\n";
                        running = false;
                        break;
                    }
                }
                else if (level == "hard")
                {
                    if (hangmanCondition == 12)
                    {
                        totalLose++;
                        hangman(hangmanCondition, level);
                        std::cout << "Failed\n";
                        running = false;
                        break;
                    }
                }
            }
        }
        play = playAgain();
        if (play == 'Y')
        {
            hangmanCondition = 1;
            running = true;
        }
        else
        {
            break;
        }
    } while (play == 'Y');
}
void playing3(std::string wordsMath[][30], std::string hintsMath[][30], int numberOfWords, int randomize, std::string selectedWord, int sizeOfSelectedWord, std::string blanks, int lives, int hangmanCondition, std::string level, int &totalWins, int &totalLose, int &totalCorrectGuess, int &totalWrongGuess)
{
    srand(time(NULL));
    bool running;
    char play;
    do
    {
        for (int i = 1; i <= 3; i++)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::cout << ".";
            if (i == 3)
            {
                sleep(1);
            }
        }
        randomize = rand() % numberOfWords;
        if (level == "easy")
        {
            selectedWord = wordsMath[0][randomize];
            lives = 7;
        }
        else if (level == "normal")
        {
            selectedWord = wordsMath[1][randomize];
            lives = 7;
        }
        else if (level == "hard")
        {
            selectedWord = wordsMath[2][randomize];
            lives = 12;
        }
        sizeOfSelectedWord = selectedWord.length();
        blanks = selectedWord;
        hangmanCondition = 1;
        running = true;
        std::string letter;

        initializeBlanks(selectedWord, blanks, sizeOfSelectedWord);
        while (running)
        {
            hangman(hangmanCondition, level);
            displayWord(blanks, sizeOfSelectedWord);
            if (!checkString(selectedWord, blanks))
            {
                totalWins++;
                break;
            }
            displayLives(lives);
            displayHint(hintsMath, randomize, level);
            letter = guessLetter();
            if (checkLetter(letter, selectedWord, sizeOfSelectedWord, blanks))
            {
                totalCorrectGuess++;
                continue;
            }
            else
            {
                lives--;
                hangmanCondition++;
                totalWrongGuess++;
                if (level == "easy" || level == "normal")
                {
                    if (hangmanCondition == 8)
                    {
                        totalLose++;
                        hangman(hangmanCondition, level);
                        std::cout << "Failed\n";
                        running = false;
                        break;
                    }
                }
                else if (level == "hard")
                {
                    if (hangmanCondition == 12)
                    {
                        totalLose++;
                        hangman(hangmanCondition, level);
                        std::cout << "Failed\n";
                        running = false;
                        break;
                    }
                }
            }
        }
        play = playAgain();
        if (play == 'Y')
        {
            hangmanCondition = 1;
            running = true;
        }
        else
        {
            break;
        }
    } while (play == 'Y');
}
void playing4(std::string wordsHumanBody[][30], std::string hintsHumanBody[][30], int numberOfWords, int randomize, std::string selectedWord, int sizeOfSelectedWord, std::string blanks, int lives, int hangmanCondition, std::string level, int &totalWins, int &totalLose, int &totalCorrectGuess, int &totalWrongGuess)
{
    srand(time(NULL));
    bool running;
    char play;
    do
    {
        for (int i = 1; i <= 3; i++)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::cout << ".";
            if (i == 3)
            {
                sleep(1);
            }
        }
        randomize = rand() % numberOfWords;
        if (level == "easy")
        {
            selectedWord = wordsHumanBody[0][randomize];
            lives = 7;
        }
        else if (level == "normal")
        {
            selectedWord = wordsHumanBody[1][randomize];
            lives = 7;
        }
        else if (level == "hard")
        {
            selectedWord = wordsHumanBody[2][randomize];
            lives = 12;
        }
        sizeOfSelectedWord = selectedWord.length();
        blanks = selectedWord;
        hangmanCondition = 1;
        running = true;
        std::string letter;

        initializeBlanks(selectedWord, blanks, sizeOfSelectedWord);
        while (running)
        {
            hangman(hangmanCondition, level);
            displayWord(blanks, sizeOfSelectedWord);
            if (!checkString(selectedWord, blanks))
            {
                totalWins++;
                break;
            }
            displayLives(lives);
            displayHint(hintsHumanBody, randomize, level);
            letter = guessLetter();
            if (checkLetter(letter, selectedWord, sizeOfSelectedWord, blanks))
            {
                totalCorrectGuess++;
                continue;
            }
            else
            {
                lives--;
                hangmanCondition++;
                totalWrongGuess++;
                if (level == "easy" || level == "normal")
                {
                    if (hangmanCondition == 8)
                    {
                        totalLose++;
                        hangman(hangmanCondition, level);
                        std::cout << "Failed\n";
                        running = false;
                        break;
                    }
                }
                else if (level == "hard")
                {
                    if (hangmanCondition == 12)
                    {
                        totalLose++;
                        hangman(hangmanCondition, level);
                        std::cout << "Failed\n";
                        running = false;
                        break;
                    }
                }
            }
        }
        play = playAgain();
        if (play == 'Y')
        {
            hangmanCondition = 1;
            running = true;
        }
        else
        {
            break;
        }
    } while (play == 'Y');
}
void playing5(std::string wordsHistory[][30], std::string hintsHistory[][30], int numberOfWords, int randomize, std::string selectedWord, int sizeOfSelectedWord, std::string blanks, int lives, int hangmanCondition, std::string level, int &totalWins, int &totalLose, int &totalCorrectGuess, int &totalWrongGuess)
{
    srand(time(NULL));
    bool running;
    char play;
    do
    {
        for (int i = 1; i <= 3; i++)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::cout << ".";
            if (i == 3)
            {
                sleep(1);
            }
        }
        randomize = rand() % numberOfWords;
        if (level == "easy")
        {
            selectedWord = wordsHistory[0][randomize];
            lives = 7;
        }
        else if (level == "normal")
        {
            selectedWord = wordsHistory[1][randomize];
            lives = 7;
        }
        else if (level == "hard")
        {
            selectedWord = wordsHistory[2][randomize];
            lives = 12;
        }
        sizeOfSelectedWord = selectedWord.length();
        blanks = selectedWord;
        hangmanCondition = 1;
        running = true;
        std::string letter;

        initializeBlanks(selectedWord, blanks, sizeOfSelectedWord);
        while (running)
        {
            hangman(hangmanCondition, level);
            displayWord(blanks, sizeOfSelectedWord);
            if (!checkString(selectedWord, blanks))
            {
                totalWins++;
                break;
            }
            displayLives(lives);
            displayHint(hintsHistory, randomize, level);
            letter = guessLetter();
            if (checkLetter(letter, selectedWord, sizeOfSelectedWord, blanks))
            {
                totalCorrectGuess++;
                continue;
            }
            else
            {
                lives--;
                hangmanCondition++;
                totalWrongGuess++;
                if (level == "easy" || level == "normal")
                {
                    if (hangmanCondition == 8)
                    {
                        totalLose++;
                        hangman(hangmanCondition, level);
                        std::cout << "Failed\n";
                        running = false;
                        break;
                    }
                }
                else if (level == "hard")
                {
                    if (hangmanCondition == 12)
                    {
                        totalLose++;
                        hangman(hangmanCondition, level);
                        std::cout << "Failed\n";
                        running = false;
                        break;
                    }
                }
            }
        }
        play = playAgain();
        if (play == 'Y')
        {
            hangmanCondition = 1;
            running = true;
        }
        else
        {
            break;
        }
    } while (play == 'Y');
}
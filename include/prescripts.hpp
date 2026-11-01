#pragma once
#include <Arduino.h>
#include <avr/pgmspace.h>
#include "prng.hpp"


static const char LOCATIONS[][24] PROGMEM = {
    "beach", "store", "house", "graveyard", "lighthouse",
    "train platform", "place you call home", "place you'd hide a body",
};

static const char PREPRESCRIPT[][64] PROGMEM = {
    "When you see a TV-headed fellow, subscribe to their Patreon.",
    "Drink three cups of water as soon as you get up.",
    "Pet quadrupedal animals five times.",
};

static const char PERSON_ADJ[][16] PROGMEM = {
    "ugly", "beautiful", "handsome", "cute", "plain",
    "young", "old", "elderly", "tall", "short",
    "kind", "mean", "shy", "bold", "quiet", "loud",
    "", "", "", "",
};

static const char PERSON_SUPER[][16] PROGMEM = {
    "ugliest", "prettiest", "kindest", "meanest",
    "most-obsessive", "most-dangerous", "most-unhinged",
    "", "", "", "", "",
};

static const char COLORS[][16] PROGMEM = {
    "blue ", "black ", "red ", "brown ", "yellow ", "pink ", "white ",
    "grey ", "green ", "cyan ", "teal ", "purple ", "orange ",
    "gold ", "silver ", "maroon ", "navy ",
    "", "", "", "",
};

static const char PERSONTYPE[][16] PROGMEM = {
    "friend", "child", "teenager", "adult", "elder", "stranger",
    "neighbor", "visitor", "passerby", "sibling", "parent",
    "teacher", "student", "priest", "fixer", "villager",
    "local", "outsider", "person", "person", "person",
};

static const char PERSONTYPE2[][24] PROGMEM = {
    "friend", "stranger", "family", "acquaintance",
    "someone familiar", "someone unknown", "person", "figure",
    "silhouette", "shape", "something alive", "something watching",
};

static const char CLOTHING[][16] PROGMEM = {
    "hat", "cap", "hoodie", "coat", "jacket", "shirt", "dress",
    "pants", "shoes", "boots", "gloves", "scarf", "mask", "glasses",
    "uniform", "costume", "ribbon",
};

static const char MATERIAL[][16] PROGMEM = {
    "cloth ", "leather ", "wool ", "cotton ", "silk ",
    "new ", "old ", "worn ", "tattered ", "torn ", "clean ", "dirty ",
    "", "", "", "",
};

static const char GAMES[][32] PROGMEM = {
    "Patty Cake", "Never Have I Ever", "Truth or Dare", "Tag",
    "Hide and Seek", "Hopscotch", "Simon Says", "Red Light Green Light",
    "Chess", "Checkers", "Dominoes", "Charades", "Would You Rather",
    "Rock Paper Scissors", "a game played in the dark",
    "a game that doesn't end", "a game you can't stop playing",
};

static const char TOPICS[][24] PROGMEM = {
    "love", "life", "death", "fear", "regret", "hope",
    "loneliness", "trust", "guilt", "desire", "your secrets",
    "your fears", "your past", "your future", "yourself",
    "memories", "dreams", "nightmares", "the city", "a movie",
    "your crush", "your favorite food", "birds", "smoke",
    "money", "reality", "religion", "science", "free will",
    "time", "home", "identity", "meaning", "purpose", "rules",
    "fire", "water", "power", "justice", "punishment",
    "family", "friendship", "intimacy", "jealousy", "obsession",
};

static const char OBJCS[][24] PROGMEM = {
    "pen and paper", "pencil", "eraser", "apples", "empty bottle",
    "glass cup", "ceramic mug", "dead plant", "bag of soil",
    "duct tape", "string", "rope", "chalk", "ash", "plastic bag",
    "wooden chair", "broken stool", "playing cards", "dice",
    "spoon", "fork", "knife", "empty plate", "crayons", "paint",
    "paintbrush", "toilet paper", "old photograph", "framed picture",
    "key", "locked box", "backpack", "paper bag", "cardboard box",
    "flashlight", "battery", "clock", "broken clock", "watch",
    "mirror", "cracked mirror", "something heavy", "something sharp",
    "something warm", "something cold", "calendar", "wallet",
    "loose change", "padlock", "shoebox", "toolbox", "first aid kit",
    "umbrella", "blanket", "pillow", "lamp", "light bulb",
    "extension cord", "old phone", "dead phone", "radio",
    "television", "camera", "clipboard", "trash bag", "map",
    "alarm clock", "timer", "ruler", "broom", "bucket", "soap bar",
    "towel", "shard of glass", "name tag", "ID card", "hammer",
    "mallet", "screwdriver", "wrench", "pliers", "handsaw",
    "box cutter", "ladder", "shovel", "rake", "brick", "chain",
    "work gloves", "hard hat", "lantern", "gas can", "cooler",
    "propane tank", "sleeping bag", "fishing rod", "crate",
    "traffic cone", "warning sign", "tire", "weapon",
};

static const char TASK0[][40] PROGMEM = {
    "", "", "", "", "", "", "", "", "", "",
    "Without seeking permission, ",
    "Continue until completion, ",
    "Repeat as necessary, ",
    "Regardless of how you feel, ",
    "Take note and, ",
    "At work, ",
    "In the next hour, ",
    "Sometime today, ",
    "At noon, ",
    "Tonight, ",
    "At midnight, ",
    "After receiving this prescript, ",
    "After a meal, ",
    "When preparing to leave your home, ",
    "While no one is watching, ",
    "As soon as you can safely do so, ",
    "The next time you are alone, ",
    "Before the end of the day, ",
    "Immediately after waking up, ",
    "Just before falling asleep, ",
    "While standing still, ",
    "During a moment of silence, ",
    "Without drawing attention to yourself, ",
    "As casually as possible, ",
};

static const char STARTER[][34] PROGMEM = {
    "", "", "", "", "", "", "", "", "", "",
    "pause briefly, ",
    "wait a moment, ",
    "continue, ",
    "proceed, ",
    "then, ",
    "look around, ",
    "look forward, ",
    "look away and ",
    "look closer and ",
    "take a step and ",
    "take another step and ",
    "stop moving and ",
    "start moving and ",
    "change direction and ",
    "stand still and ",
    "take a breath and ",
    "hold your breath briefly and ",
    "count silently and ",
    "wait and ",
    "focus and ",
    "pay attention and ",
    "consider this and ",
    "do nothing and ",
    "act naturally and ",
    "close your eyes briefly and ",
    "open your eyes and ",
    "look over your shoulder and ",
    "adjust your posture and ",
    "walk slowly and ",
    "walk quickly and ",
    "stop walking and ",
    "think about what comes next and ",
    "hesitate briefly and then ",
};

static const char ADDITIONAL[][24] PROGMEM = {
    "", "", "", "", "", "", "", "", "", "", "", "",
    " backwards", " slowly", " carefully", " without stopping",
    " without speaking", " without looking back", " twice", " alone",
    " with no witnesses", " while being observed", " in silence",
    " standing up", " sitting down", " lying down", " indoors",
    " outdoors", " nearby", " far away", " in complete darkness",
    " in bright light", " before sunrise", " after sunset",
    " at dawn", " at dusk", " as quickly as you can",
    " if you feel upset", " in public", " with your eyes closed",
};

static const char TRANSITIONS[][24] PROGMEM = {
    ", then ", " and ", ". After, ", ", and then ",
    ", and immediately ", ", afterward, ", ", shortly after, ",
    ", soon after, ", ", eventually, ", ". Then ", ". Next, ",
    ". Afterward, ", ". Immediately, ", ", while doing so, ",
    ", at the same time, ", ", meanwhile, ", ", without pause, ",
    ", without delay, ",
};

static const char FOLLOWUPS[][42] PROGMEM = {
    "proceed to light them on fire.",
    "ask them to marry you.",
    "discard this prescript.",
    "make them a nice meal.",
    "make sure they never talk again.",
    "carve this prescript into them.",
    "eat them.",
    "start a family with them.",
    "go home.",
    "go to a graveyard.",
    "remain where you are.",
    "resume your previous activity.",
    "do nothing further.",
    "apologize without explaining why.",
    "pretend you misunderstood everything.",
    "change the subject unexpectedly.",
    "wait for further instructions.",
    "leave without acknowledging them.",
};

static const char FOLLOWUPS2[][64] PROGMEM = {
    "Their gender does not matter.",
    "You must sleep 5 hours tonight.",
    "You must hold your breath during the interaction.",
    "Ensure that you do not blink.",
    "You must disobey your next prescript.",
    "You must believe the lie you are told.",
    "Climb into the freezer and wait 5 hours.",
    "You are not allowed to contact them after.",
    "You must keep in contact with them for the next 5 hours.",
    "You cannot talk after 9pm.",
    "Make sure you tell them to look behind them.",
    "Take a bath for 5 minutes to clean yourself.",
    "You must wash your hands before and after the interaction.",
    "You must not touch them again after this.",
    "You must not say their name out loud.",
    "You must not discuss this with anyone.",
    "You must avoid public places for the rest of the day.",
    "You must not look back while leaving.",
    "You must sleep on your back tonight.",
    "You must wake up without an alarm.",
    "Outcome is irrelevant.",
    "You are only allowed to cry after it is done.",
};

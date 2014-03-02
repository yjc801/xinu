static unsigned char words[2048][5] = {
  "AAAA", "ABBR", "ABBY", "ABCD", "ABED", "ABEL", "ABET", "ABLE", 
  "ABUT", "ACES", "ACHE", "ACHY", "ACID", "ACME", "ACNE", "ACRE", 
  "ACTS", "ADAM", "ADDS", "AFAR", "AFRO", "AGED", "AGES", "AHAB", 
  "AHEM", "AHOY", "AIDE", "AIMS", "AIRY", "AJAR", "AJAX", "AKIN", 
  "AKQJ", "ALAN", "ALAS", "ALEC", "ALEX", "ALLY", "ALMA", "ALMS", 
  "ALPS", "ALSO", "ALTO", "ALUM", "ALYX", "AMEN", "AMES", "AMID", 
  "AMMO", "AMOK", "AMOS", "AMPS", "ANAL", "ANDY", "ANEW", "ANNA", 
  "ANNE", "ANON", "ANTE", "ANTI", "ANTS", "ANUS", "APES", "APEX", 
  "AQUA", "ARAB", "ARCH", "ARCS", "AREA", "ARIA", "ARID", "ARMS", 
  "ARMY", "ARTS", "ARTY", "ASAP", "ASHY", "ASIA", "ASKS", "ASSN", 
  "ATOM", "ATOP", "ATTN", "AUNT", "AURA", "AUTO", "AVID", "AVIS", 
  "AVON", "AVOW", "AWAY", "AWED", "AWOL", "AWRY", "AXES", "AXIS", 
  "AXLE", "BAAL", "BABE", "BABY", "BACH", "BACK", "BAGS", "BAIL", 
  "BAIT", "BAKE", "BALD", "BALE", "BALI", "BALK", "BALL", "BALM", 
  "BAND", "BANE", "BANG", "BANK", "BARB", "BARD", "BARE", "BARF", 
  "BARK", "BARN", "BARS", "BART", "BASE", "BASH", "BASK", "BASS", 
  "BATH", "BATS", "BAUD", "BAWD", "BAWL", "BAYS", "BBBB", "BEAD", 
  "BEAK", "BEAM", "BEAN", "BEAR", "BEAT", "BEAU", "BECK", "BEDS", 
  "BEEF", "BEEN", "BEEP", "BEER", "BEES", "BEET", "BEGS", "BELL", 
  "BELT", "BEND", "BENT", "BENZ", "BERG", "BERT", "BESS", "BEST", 
  "BETA", "BETH", "BETS", "BEVY", "BIAS", "BIDE", "BIDS", "BIER", 
  "BIKE", "BILE", "BILK", "BILL", "BIND", "BIRD", "BITE", "BITS", 
  "BLAB", "BLAH", "BLAT", "BLDG", "BLED", "BLEW", "BLIP", "BLOB", 
  "BLOC", "BLOT", "BLOW", "BLUE", "BLUR", "BLVD", "BOAR", "BOAT", 
  "BOBS", "BODE", "BODY", "BOGS", "BOIL", "BOLD", "BOLT", "BOMB", 
  "BOND", "BONE", "BONG", "BONN", "BONY", "BOOB", "BOOK", "BOOM", 
  "BOON", "BOOR", "BOOT", "BORE", "BORG", "BORN", "BOSS", "BOTH", 
  "BOUT", "BOWL", "BOWS", "BOXY", "BOYD", "BOYS", "BOZO", "BRAD", 
  "BRAG", "BRAN", "BRAT", "BRAY", "BRED", "BREW", "BRIG", "BRIM", 
  "BROW", "BUCK", "BUDS", "BUFF", "BUGS", "BULB", "BULK", "BULL", 
  "BUMP", "BUMS", "BUNK", "BUNS", "BUNT", "BUOY", "BURG", "BURN", 
  "BURP", "BURT", "BURY", "BUSH", "BUSS", "BUST", "BUSY", "BUTT", 
  "BUYS", "BUZZ", "BYOB", "BYRD", "BYTE", "CAFE", "CAGE", "CAIN", 
  "CAKE", "CALF", "CALL", "CALM", "CAME", "CAMP", "CANE", "CANS", 
  "CAPE", "CARD", "CARE", "CARL", "CARP", "CARS", "CART", "CASE", 
  "CASH", "CASK", "CAST", "CATS", "CAVE", "CCCC", "CCCP", "CEDE", 
  "CELL", "CENT", "CHAD", "CHAP", "CHAR", "CHAT", "CHEF", "CHEW", 
  "CHIC", "CHIN", "CHIP", "CHIT", "CHOP", "CHOW", "CHUB", "CHUG", 
  "CHUM", "CIAO", "CITE", "CITY", "CLAD", "CLAM", "CLAN", "CLAP", 
  "CLAW", "CLAY", "CLEF", "CLEM", "CLEO", "CLIP", "CLOD", "CLOG", 
  "CLOT", "CLOY", "CLUB", "CLUE", "COAL", "COAT", "COAX", "COCA", 
  "COCK", "CODA", "CODE", "CODY", "COED", "COGS", "COIF", "COIL", 
  "COIN", "COKE", "COLA", "COLD", "COLE", "COLT", "COMA", "COMB", 
  "COME", "CONE", "COOK", "COOL", "COON", "COOP", "COOS", "COOT", 
  "COPE", "COPS", "COPY", "CORD", "CORE", "CORK", "CORN", "CORP", 
  "COST", "COUP", "COVE", "COWL", "COWS", "COZY", "CRAB", "CRAG", 
  "CRAM", "CRAP", "CREW", "CRIB", "CROP", "CROW", "CRUD", "CRUX", 
  "CUBA", "CUBE", "CUBS", "CUES", "CUFF", "CULL", "CULT", "CUPS", 
  "CURB", "CURD", "CURE", "CURL", "CURT", "CUSP", "CUSS", "CUTE", 
  "CUTS", "CYST", "CZAR", "DAFT", "DAIS", "DALE", "DAME", "DAMN", 
  "DAMP", "DANA", "DANE", "DANG", "DANK", "DARE", "DARK", "DARN", 
  "DART", "DASH", "DATA", "DATE", "DAUB", "DAVE", "DAVY", "DAWN", 
  "DAYS", "DAZE", "DBMS", "DDDD", "DEAD", "DEAF", "DEAL", "DEAN", 
  "DEAR", "DEBT", "DECK", "DEED", "DEEM", "DEEP", "DEER", "DEFT", 
  "DEFY", "DELI", "DEMO", "DENT", "DENY", "DEPT", "DESK", "DEWY", 
  "DIAL", "DIBS", "DICE", "DICK", "DIED", "DIES", "DIET", "DIGS", 
  "DIKE", "DILL", "DIME", "DIMS", "DINE", "DING", "DINT", "DIPS", 
  "DIRE", "DIRK", "DIRT", "DISC", "DISH", "DISK", "DIVA", "DIVE", 
  "DOCK", "DODO", "DOES", "DOFF", "DOGS", "DOLE", "DOLL", "DOLT", 
  "DOME", "DONE", "DOOM", "DOOR", "DOPE", "DORA", "DORM", "DOSE", 
  "DOTE", "DOTS", "DOUG", "DOVE", "DOWN", "DOZE", "DRAB", "DRAG", 
  "DRAW", "DREW", "DRIP", "DROP", "DRUB", "DRUG", "DRUM", "DUAL", 
  "DUCK", "DUCT", "DUDE", "DUEL", "DUES", "DUET", "DUFF", "DUKE", 
  "DULL", "DULY", "DUMB", "DUMP", "DUNE", "DUNG", "DUNK", "DUPE", 
  "DUSK", "DUST", "DUTY", "DYAD", "DYED", "EACH", "EARL", "EARN", 
  "EARS", "EASE", "EAST", "EASY", "EATS", "EAVE", "ECHO", "EDDY", 
  "EDEN", "EDGE", "EDGY", "EDIT", "EDNA", "EEEE", "EGGS", "ELKS", 
  "ELLA", "ELMS", "ELSE", "EMIL", "EMIT", "EMMA", "EMMY", "ENDS", 
  "ENVY", "EONS", "EPIC", "ERGO", "ERIC", "ERIE", "ERIK", "ERIN", 
  "EROS", "ESPY", "ETCH", "EVEN", "EVER", "EVIL", "EXAM", "EXEC", 
  "EXIT", "EXPO", "EYED", "EYES", "EZRA", "FACE", "FACT", "FADE", 
  "FADS", "FAIL", "FAIR", "FAKE", "FALL", "FAME", "FANG", "FANS", 
  "FARE", "FARM", "FAST", "FATE", "FATS", "FAUX", "FAWN", "FAZE", 
  "FEAR", "FEAT", "FEED", "FEEL", "FEES", "FEET", "FELL", "FELT", 
  "FEND", "FERN", "FETE", "FEUD", "FFFF", "FIAT", "FIDO", "FIFE", 
  "FIGS", "FIJI", "FILE", "FILL", "FILM", "FIND", "FINE", "FINK", 
  "FINN", "FIRE", "FIRM", "FISH", "FIST", "FITS", "FIVE", "FIZZ", 
  "FLAB", "FLAG", "FLAK", "FLAP", "FLAT", "FLAW", "FLAX", "FLAY", 
  "FLEA", "FLED", "FLEE", "FLEW", "FLEX", "FLIP", "FLIT", "FLOG", 
  "FLOP", "FLOW", "FLUB", "FLUE", "FLUX", "FOAL", "FOAM", "FOES", 
  "FOGY", "FOIL", "FOLD", "FOLK", "FOND", "FONT", "FOOD", "FOOL", 
  "FOOT", "FORD", "FORE", "FORK", "FORM", "FORT", "FOUL", "FOUR", 
  "FOWL", "FOXY", "FRAU", "FRAY", "FRED", "FREE", "FRET", "FROG", 
  "FROM", "FUEL", "FUJI", "FULL", "FUME", "FUND", "FUNK", "FURL", 
  "FURS", "FURY", "FUSE", "FUSS", "FUZZ", "GAEA", "GAGS", "GAIL", 
  "GAIN", "GAIT", "GALA", "GALE", "GALL", "GAME", "GAMY", "GANG", 
  "GAPE", "GAPS", "GARB", "GARY", "GASH", "GASP", "GATE", "GAVE", 
  "GAWK", "GAZE", "GEAR", "GELD", "GEMS", "GENE", "GENT", "GERM", 
  "GETS", "GGGG", "GIFT", "GILA", "GILD", "GILL", "GILT", "GINA", 
  "GINO", "GIRD", "GIRL", "GIST", "GIVE", "GLAD", "GLEE", "GLEN", 
  "GLIB", "GLOB", "GLOW", "GLUE", "GLUM", "GLUT", "GNAT", "GNAW", 
  "GOAD", "GOAL", "GOAT", "GODS", "GOES", "GOGH", "GOGO", "GOLD", 
  "GOLF", "GONE", "GONG", "GOOD", "GOOF", "GOON", "GORE", "GORY", 
  "GOSH", "GOUT", "GOVT", "GOWN", "GRAB", "GRAD", "GRAM", "GRAY", 
  "GREG", "GREW", "GREY", "GRID", "GRIM", "GRIN", "GRIP", "GRIT", 
  "GROG", "GROW", "GRUB", "GUAM", "GULF", "GULL", "GULP", "GUNK", 
  "GUNS", "GURU", "GUSH", "GUST", "GUTS", "GUYS", "GWEN", "GYRO", 
  "HACK", "HAHA", "HAIL", "HAIR", "HALF", "HALL", "HALO", "HALT", 
  "HAMS", "HAND", "HANG", "HANK", "HANS", "HARD", "HARE", "HARK", 
  "HARM", "HARP", "HART", "HARV", "HASH", "HASP", "HATE", "HATS", 
  "HAUL", "HAVE", "HAWK", "HAZE", "HAZY", "HDTV", "HEAD", "HEAL", 
  "HEAP", "HEAR", "HEAT", "HECK", "HEED", "HEEL", "HEFT", "HEIR", 
  "HELD", "HELL", "HELM", "HELP", "HEMP", "HEMS", "HENS", "HERB", 
  "HERD", "HERE", "HERO", "HERR", "HERS", "HHHH", "HICK", "HIDE", 
  "HIGH", "HIKE", "HILL", "HILT", "HIND", "HINT", "HIPS", "HIRE", 
  "HISS", "HITS", "HIVE", "HOAX", "HOBO", "HOCK", "HOGS", "HOLD", 
  "HOLE", "HOLY", "HOME", "HONE", "HONK", "HOOD", "HOOF", "HOOK", 
  "HOOP", "HOOT", "HOPE", "HOPS", "HORN", "HOSE", "HOST", "HOUR", 
  "HOWL", "HUBS", "HUES", "HUEY", "HUFF", "HUGE", "HUGH", "HUGO", 
  "HUGS", "HULA", "HULK", "HULL", "HUMP", "HUMS", "HUNG", "HUNK", 
  "HUNT", "HURL", "HURT", "HUSH", "HUSK", "HYDE", "HYMN", "HYPE", 
  "HYPO", "IBID", "ICBM", "ICED", "ICKY", "ICON", "IDEA", "IDLE", 
  "IDLY", "IDOL", "IFFY", "IGOR", "IIII", "IMPS", "INCA", "INCH", 
  "INDY", "INFO", "INKY", "INNS", "INTO", "IONS", "IOTA", "IOWA", 
  "IRAN", "IRAQ", "IRIS", "IRMA", "IRON", "ISLE", "ITCH", "ITEM", 
  "IVAN", "JACK", "JADE", "JAIL", "JAMB", "JANE", "JARS", "JAVA", 
  "JAWS", "JAZZ", "JEAN", "JEDI", "JEEP", "JEER", "JEFF", "JERK", 
  "JEST", "JETS", "JIGS", "JILL", "JILT", "JINX", "JIVE", "JJJJ", 
  "JOAN", "JOBS", "JOCK", "JODY", "JOEL", "JOEY", "JOGS", "JOHN", 
  "JOIN", "JOKE", "JOLT", "JOSE", "JOSH", "JOTS", "JOVE", "JOWL", 
  "JUAN", "JUDE", "JUDO", "JUDY", "JUGS", "JULY", "JUMP", "JUNE", 
  "JUNG", "JUNK", "JUNO", "JURY", "JUST", "JUTE", "KALE", "KANE", 
  "KANT", "KARL", "KATE", "KAYO", "KEEL", "KEEN", "KEEP", "KEGS", 
  "KELP", "KENT", "KEPT", "KEYS", "KHAN", "KICK", "KIDS", "KILL", 
  "KILN", "KILO", "KILT", "KIND", "KING", "KINK", "KIRK", "KISS", 
  "KITE", "KIWI", "KKKK", "KLAN", "KNEE", "KNEW", "KNIT", "KNOB", 
  "KNOT", "KNOW", "KNOX", "KOAN", "KONG", "KOOK", "KRIS", "KUDO", 
  "KURT", "LABS", "LACE", "LACK", "LACY", "LADS", "LADY", "LAGS", 
  "LAID", "LAIR", "LAKE", "LAMB", "LAME", "LAMP", "LANA", "LAND", 
  "LANE", "LAOS", "LAPS", "LARA", "LARD", "LARK", "LASH", "LASS", 
  "LAST", "LATE", "LAUD", "LAVA", "LAWN", "LAWS", "LAYS", "LAZY", 
  "LEAD", "LEAF", "LEAH", "LEAK", "LEAN", "LEAP", "LEAR", "LEDA", 
  "LEER", "LEFT", "LEGS", "LEND", "LENS", "LENT", "LEON", "LESS", 
  "LEST", "LETS", "LEVY", "LEWD", "LIAR", "LICE", "LICK", "LIDS", 
  "LIED", "LIEN", "LIES", "LIEU", "LIFE", "LIFT", "LIKE", "LILT", 
  "LILY", "LIMA", "LIMB", "LIME", "LIMP", "LINE", "LINK", "LINT", 
  "LION", "LIPS", "LIRA", "LISA", "LISP", "LIST", "LIVE", "LIZA", 
  "LLLL", "LOAD", "LOAF", "LOAM", "LOAN", "LOBE", "LOBS", "LOCH", 
  "LOCK", "LODE", "LOFT", "LOGO", "LOGS", "LOIN", "LOIS", "LOKI", 
  "LOLA", "LOLL", "LONE", "LONG", "LOOK", "LOOM", "LOON", "LOOP", 
  "LOOT", "LOPS", "LORD", "LORE", "LOSE", "LOSS", "LOST", "LOTS", 
  "LOUD", "LOUT", "LOVE", "LUAU", "LUCE", "LUCK", "LUCY", "LUGS", 
  "LUIS", "LUKE", "LULL", "LULU", "LUMP", "LUNA", "LUNG", "LURE", 
  "LURK", "LUSH", "LUST", "LUTE", "LYLE", "LYNN", "LYNX", "LYRE", 
  "MACE", "MADE", "MAID", "MAIL", "MAIM", "MAIN", "MAKE", "MALE", 
  "MALL", "MALT", "MAMA", "MANE", "MANY", "MAPS", "MARE", "MARK", 
  "MARS", "MART", "MARX", "MARY", "MASH", "MASK", "MASS", "MAST", 
  "MATE", "MATH", "MATS", "MATT", "MAUD", "MAUL", "MAYO", "MAZE", 
  "MEAL", "MEAN", "MEAT", "MEEK", "MEET", "MELD", "MELT", "MEMO", 
  "MEND", "MENU", "MEOW", "MERE", "MESA", "MESH", "MESS", "MGMT", 
  "MICE", "MIGS", "MIKE", "MILD", "MILE", "MILK", "MILL", "MILO", 
  "MIME", "MIMI", "MIND", "MINE", "MINI", "MINK", "MINT", "MIRE", 
  "MIRV", "MISC", "MISS", "MIST", "MITE", "MITT", "MMMM", "MOAN", 
  "MOAT", "MOBS", "MOBY", "MOCK", "MODE", "MOJO", "MOLD", "MOLE", 
  "MOLT", "MONA", "MONK", "MONO", "MOOD", "MOON", "MOOR", "MOPE", 
  "MOPS", "MORE", "MORN", "MORT", "MOSS", "MOST", "MOTE", "MOTH", 
  "MOVE", "MOWS", "MUCH", "MUCK", "MUFF", "MUGS", "MULE", "MULL", 
  "MURK", "MUSE", "MUSH", "MUSK", "MUSS", "MUST", "MUTE", "MUTT", 
  "MYOB", "MYRA", "MYTH", "NABS", "NACL", "NAGS", "NAIL", "NAME", 
  "NAPE", "NAPS", "NASA", "NASH", "NATE", "NATO", "NAVY", "NAZI", 
  "NEAR", "NEAT", "NECK", "NEED", "NEIL", "NELL", "NEON", "NERD", 
  "NEST", "NETS", "NEWS", "NEWT", "NEXT", "NICE", "NICK", "NICO", 
  "NILE", "NINA", "NINE", "NIPS", "NNNN", "NOAH", "NODE", "NODS", 
  "NOEL", "NONE", "NONO", "NOOK", "NOON", "NOPE", "NORA", "NORM", 
  "NOSE", "NOSY", "NOTE", "NOUN", "NOVA", "NUDE", "NUKE", "NULL", 
  "NUMB", "NUNS", "NUTS", "OARS", "OATH", "OATS", "OBEY", "OBIT", 
  "OBOE", "ODDS", "ODOR", "OGLE", "OGRE", "OHIO", "OILS", "OILY", 
  "OINK", "OKAY", "OKRA", "OLAF", "OLGA", "OMEN", "OMIT", "ONCE", 
  "ONLY", "ONTO", "OOOO", "OOPS", "OOZE", "OPAL", "OPEC", "OPEN", 
  "OPUS", "ORAL", "ORBS", "ORGY", "OTIS", "OTTO", "OUCH", "OURS", 
  "OUST", "OVAL", "OVEN", "OVER", "OWED", "OWES", "OWLS", "OWNS", 
  "OXEN", "PACE", "PACK", "PACT", "PADS", "PAGE", "PAID", "PAIL", 
  "PAIN", "PAIR", "PALE", "PALM", "PALS", "PANE", "PANG", "PANS", 
  "PANT", "PAPA", "PARE", "PARK", "PART", "PASS", "PAST", "PATH", 
  "PATS", "PAUL", "PAVE", "PAWN", "PAWS", "PEAK", "PEAR", "PEAS", 
  "PECK", "PEED", "PEEK", "PEEL", "PEEP", "PEER", "PEGS", "PELT", 
  "PENN", "PENS", "PERK", "PERM", "PERT", "PERU", "PESO", "PEST", 
  "PETE", "PETS", "PHIL", "PICK", "PIER", "PIES", "PIGS", "PIKE", 
  "PILE", "PILL", "PIMP", "PINE", "PING", "PINK", "PINS", "PINT", 
  "PIPE", "PITA", "PITH", "PITS", "PITY", "PLAN", "PLAY", "PLEA", 
  "PLOD", "PLOP", "PLOT", "PLOW", "PLOY", "PLUG", "PLUM", "PLUS", 
  "PODS", "POEM", "POET", "POGO", "POKE", "POLE", "POLK", "POLL", 
  "POLO", "POMP", "POND", "PONY", "POOH", "POOL", "POOP", "POOR", 
  "POPE", "POPS", "PORE", "PORK", "PORN", "PORT", "POSE", "POSH", 
  "POST", "POSY", "POTS", "POUR", "POUT", "PPPP", "PRAY", "PREP", 
  "PREY", "PRIG", "PRIM", "PROD", "PROF", "PROM", "PROP", "PROW", 
  "PUBS", "PUCK", "PUFF", "PUKE", "PULL", "PULP", "PUMA", "PUMP", 
  "PUNK", "PUNS", "PUNT", "PUNY", "PURE", "PURR", "PUSH", "PUTS", 
  "PUTT", "PYRE", "QQQQ", "QUAD", "QUIP", "QUIT", "QUIZ", "RACE", 
  "RACK", "RACY", "RAFT", "RAGE", "RAGS", "RAID", "RAIL", "RAIN", 
  "RAKE", "RAMP", "RAMS", "RAND", "RANG", "RANK", "RANT", "RAPE", 
  "RAPS", "RARE", "RASH", "RATE", "RATS", "RAVE", "RAYS", "RAZE", 
  "READ", "REAL", "REAP", "REAR", "REDO", "REED", "REEF", "REEK", 
  "REEL", "REFS", "REGS", "REID", "REIN", "RELY", "RENA", "REND", 
  "RENO", "RENT", "REPS", "REST", "RIBS", "RICE", "RICH", "RICK", 
  "RICO", "RIDE", "RIFT", "RIGS", "RIMS", "RIND", "RING", "RINK", 
  "RIOT", "RIPE", "RIPS", "RISE", "RISK", "RITE", "ROAD", "ROAM", 
  "ROAR", "ROBE", "ROBS", "ROCK", "RODE", "RODS", "ROLE", "ROLL", 
  "ROME", "ROMP", "ROOF", "ROOK", "ROOM", "ROOT", "ROPE", "ROSA", 
  "ROSE", "ROSS", "ROSY", "ROTE", "ROTH", "ROTS", "ROUT", "ROWS", 
  "RRRR", "RSVP", "RUBE", "RUBS", "RUBY", "RUDE", "RUDY", "RUGS", 
  "RUIN", "RULE", "RUMP", "RUNE", "RUNG", "RUNS", "RUNT", "RUSE", 
  "RUSH", "RUSS", "RUST", "RUTH", "RUTS", "RYAN", "SACK", "SAFE", 
  "SAGA", "SAGE", "SAGS", "SAID", "SAIL", "SAKE", "SALE", "SALK", 
  "SALT", "SAME", "SAND", "SANE", "SANG", "SANK", "SAPS", "SARA", 
  "SASE", "SASH", "SAUL", "SAVE", "SAWS", "SAYS", "SCAB", "SCAM", 
  "SCAN", "SCAR", "SCAT", "SCOT", "SCOW", "SCUM", "SEAL", "SEAM", 
  "SEAN", "SEAR", "SEAS", "SEAT", "SECT", "SEED", "SEEK", "SEEM", 
  "SEEN", "SEEP", "SEER", "SEES", "SELF", "SELL", "SEMI", "SEND", 
  "SENT", "SERB", "SERF", "SETH", "SETS", "SEWN", "SEWS", "SEXY", 
  "SHAM", "SHAW", "SHEA", "SHED", "SHIN", "SHIP", "SHOE", "SHOO", 
  "SHOP", "SHOT", "SHOW", "SHUN", "SHUT", "SICK", "SIDE", "SIFT", 
  "SIGH", "SIGN", "SILK", "SILL", "SILO", "SILT", "SIMS", "SING", 
  "SINK", "SINS", "SIPS", "SIRE", "SITE", "SITS", "SIZE", "SKEW", 
  "SKID", "SKIM", "SKIN", "SKIP", "SKIS", "SKIT", "SLAB", "SLAM", 
  "SLAP", "SLAW", "SLAY", "SLED", "SLEW", "SLID", "SLIM", "SLIP", 
  "SLIT", "SLOB", "SLOG", "SLOP", "SLOT", "SLOW", "SLUG", "SLUM", 
  "SLUR", "SMOG", "SMUG", "SMUT", "SNAG", "SNAP", "SNIP", "SNOB", 
  "SNOT", "SNOW", "SNUB", "SNUG", "SOAK", "SOAP", "SOAR", "SOBS", 
  "SOCK", "SODA", "SOFA", "SOFT", "SOIL", "SOLD", "SOLE", "SOLO", 
  "SOME", "SONG", "SONS", "SONY", "SOON", "SOOT", "SORE", "SORT", 
  "SOUL", "SOUP", "SOUR", "SOWN", "SOWS", "SPAM", "SPAN", "SPAR", 
  "SPAS", "SPAT", "SPAY", "SPEC", "SPED", "SPEW", "SPIN", "SPIT", 
  "SPOT", "SPRY", "SPUD", "SPUN", "SPUR", "SSSS", "STAB", "STAG", 
  "STAN", "STAR", "STAT", "STAY", "STEM", "STEP", "STEW", "STIR", 
  "STOP", "STOW", "STUB", "STUD", "STUN", "STYX", "SUBS", "SUCH", 
  "SUCK", "SUDS", "SUED", "SUES", "SUEY", "SUIT", "SULK", "SUMO", 
  "SUMS", "SUNG", "SUNK", "SUNS", "SUPT", "SURE", "SURF", "SUZY", 
  "SVEN", "SWAB", "SWAG", "SWAM", "SWAN", "SWAP", "SWAT", "SWAY", 
  "SWIG", "SWIM", "SWUM", "TABS", "TABU", "TACK", "TACO", "TACT", 
  "TAFT", "TAGS", "TAIL", "TAKE", "TALE", "TALK", "TALL", "TAME", 
  "TANG", "TANK", "TANS", "TAPE", "TAPS", "TARP", "TART", "TASK", 
  "TATE", "TAUT", "TAXI", "TBSP", "TEAK", "TEAM", "TEAR", "TECH", 
  "TEEN", "TEES", "TELL", "TEMP", "TEND", "TENS", "TENT", "TERM", 
  "TEST", "TEXT", "TGIF", "THAI", "THAN", "THAT", "THAW", "THEM", 
  "THEN", "THEY", "THIN", "THIS", "THOR", "THRU", "THUD", "THUG", 
  "THUR", "THUS", "TICK", "TICS", "TIDE", "TIDY", "TIED", "TIER", 
  "TIES", "TILE", "TILL", "TILT", "TIME", "TINA", "TINT", "TINY", 
  "TIPS", "TIRE", "TOAD", "TOBY", "TODD", "TOES", "TOFU", "TOGA", 
  "TOIL", "TOLD", "TOLL", "TOMB", "TONE", "TONI", "TONS", "TONY", 
  "TOOK", "TOOL", "TOOT", "TOPS", "TORE", "TORN", "TORT", "TORY", 
  "TOSS", "TOTE", "TOTS", "TOUR", "TOUT", "TOWN", "TOWS", "TOYS", 
  "TRAP", "TRAY", "TREE", "TREK", "TRIG", "TRIM", "TRIO", "TRIP", 
  "TROT", "TROY", "TRUE", "TSAR", "TTTT", "TUBA", "TUBE", "TUBS", 
  "TUCK", "TUES", "TUFT", "TUGS", "TUNA", "TUNE", "TURF", "TURK", 
  "TURN", "TUSH", "TUSK", "TUTU", "TWIG", "TWIN", "TWIT", "TWOS", 
  "TYKE", "TYPE", "TYPO", "UGLY", "UNDO", "UNIT", "UNIX", "UNTO", 
  "UPON", "URGE", "USAF", "USED", "USES", "USIA", "USSR", "UTAH", 
  "UUUU", "VAIN", "VALE", "VAMP", "VANE", "VANS", "VARY", "VASE", 
  "VAST", "VATS", "VEAL", "VEEP", "VEER", "VEIL", "VEIN", "VEND", 
  "VENT", "VERA", "VERB", "VERN", "VERY", "VEST", "VETO", "VETS", 
  "VIAL", "VICE", "VIET", "VIEW", "VIII", "VILE", "VINE", "VISA", 
  "VISE", "VITO", "VIVA", "VLAD", "VOID", "VOLT", "VOTE", "VOWS", 
  "VTOL", "VVVV", "WADE", "WAGE", "WAGS", "WAIF", "WAIL", "WAIT", 
  "WAKE", "WALK", "WALL", "WALT", "WAND", "WANG", "WANT", "WARD", 
  "WARM", "WARN", "WARP", "WARS", "WART", "WARY", "WASH", 
};

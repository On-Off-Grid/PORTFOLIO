/* ==========================================================================
   SOUHAIL OUICHOU — PORTFOLIO / i18n.js
   Bilingual EN/FR layer: one HTML file, one dictionary, data-i18n attributes.
   - Resolution order: ?lang= URL param -> localStorage -> browser -> en
   - Runs at end of <body> (before script.js) so GSAP animates the strings
     that are actually displayed.
   - Swap modes: [data-i18n] textContent, [data-i18n-html] innerHTML,
     [data-i18n-aria] aria-label, [data-i18n-alt] alt, [data-i18n-title] title
   - On toggle: persists the choice, swaps text in place (no reload), updates
     <html lang>, document.title and the meta description, then fires the
     "i18n:applied" event so script.js can re-label stateful controls.
   ========================================================================== */
(function () {
  "use strict";

  /* --------------------------------------------------------------- dictionary */
  var I18N = {
    en: {
      "skip": "Skip to content",
      "cursor.view": "VIEW",
      "logo.aria": "Souhail Ouichou — home",
      "nav.status": `<span class="nav__pulse" aria-hidden="true"></span>Available for opportunities`,
      "nav.primary": "Primary",
      "nav.mobile": "Mobile",
      "nav.work": `<span>01</span>Work`,
      "nav.about": `<span>02</span>About`,
      "nav.path": `<span>03</span>Path`,
      "nav.exp": `<span>04</span>Experience`,
      "nav.contact": `<span>05</span>Contact`,
      "theme.title": "Toggle light / dark",
      "theme.toLight": "Switch to light theme",
      "theme.toDark": "Switch to dark theme",
      "menu.open": "Open menu",
      "menu.close": "Close menu",
      "lang.toFr": "Switch to French",
      "lang.toEn": "Switch to English",
      "portrait.alt": "Portrait of Souhail Ouichou wearing a cap and glasses",
      "hero.eyebrow": `C &amp; C++ <span>·</span> Systems <span>·</span> Networks <span>·</span> Agents`,
      "hero.l1": "Learning",
      "hero.l2": "systems",
      "hero.l3": "from the",
      "hero.l4": `bottom up<span class="accent">.</span>`,
      "hero.lede": "I'm Souhail, a Morocco-based software builder. I learned the foundations through C, C++, Linux, processes, sockets and containers; now I'm extending that base into embedded systems, security tooling and LLM-agent harnesses. This is a record of what I have built, what I understand, and what I am still trying to understand.",
      "hero.cta": "View my work",
      "hero.scroll": "Scroll to explore",
      "github.aria": "View Souhail Ouichou's GitHub profile",
      "marquee.words": `C <em>·</em> C++ <em>·</em> Linux <em>·</em> Processes <em>·</em> Threads <em>·</em> Networking <em>·</em> Embedded Systems <em>·</em> Security Tooling <em>·</em> LLM Agents <em>·</em> IoT <em>·</em> `,
      "statement.label": "01 — Profile",
      "statement.title": `I came to software through<br>construction sites, store<br>operations and unfinished paths—<br>not a straight career ladder.`,
      "statement.note": `Those environments taught me to <span>coordinate people</span>, <span>inspect failures</span> and <span>adapt under pressure</span>.`,
      "about.label": "About me",
      "about.lead": "I'm Souhail Ouichou, based in Morocco. Before software, I worked in construction and retail operations, where plans met delays, limited resources and real people.",
      "about.p2": "That background still shapes how I build: inspect the system, find the constraint, communicate clearly, and make the next useful thing work. My technical base is modest but real: C, C++, Linux, processes, threads, sockets and Docker.",
      "about.p3": "More recently, I've been exploring LLM agents, orchestration and security automation — sometimes writing the implementation myself, sometimes directing agents through specifications, tests and review.",
      "about.p4": "I left 1337 without completing the cursus. The experience still gave me difficult projects and a stronger preference for honest work over borrowed appearances. I'm now consolidating those foundations, building independently, and looking for an internship where curiosity, accountability and visible learning matter.",
      "projects.label": "02 — Selected Work",
      "projects.title": `Things I've<br>built — by hand,<br>and <span class="accent">with agents.</span>`,
      "projects.byHand": "Built by hand",
      "projects.byHandNote": "Curriculum and personal projects where I wrote and debugged the implementation directly.",
      "projects.byHandContext": "Most of these were implemented during the 42/1337 curriculum under C99, C++98 and restricted-library constraints.",
      "projects.withAgents": "Built with agents",
      "projects.withAgentsNote": "I owned the problem framing, architecture, specifications, review and iteration; LLM agents produced substantial implementation work. Repository notes explain the division of labor.",
      "card.featured": "Featured",
      "card.viewGithub": "View on GitHub",
      "aria.minishell": "View minishell on GitHub",
      "aria.philosophers": "View philosophers on GitHub",
      "aria.minitalk": "View minitalk on GitHub",
      "aria.myirc": "View my_irc on GitHub",
      "aria.cpps": "View CPPS on GitHub",
      "aria.cub3d": "View cub3d on GitHub",
      "aria.fractol": "View fractol on GitHub",
      "aria.inception": "View inception on GitHub",
      "aria.gransense": "View IgranSense MVP on GitHub",
      "aria.harness": "View bug-bounty harness on GitHub",
      "aria.ult": "View Ult Harness on GitHub",
      "dom.systems": "Systems / C",
      "dom.concurrency": "Concurrency / C",
      "dom.networking": "Networking / C++",
      "dom.oop": "OOP / C++",
      "dom.graphics": "Graphics / C",
      "dom.fullstack": "Full-stack / AI",
      "dom.agents": "Agents / Security",
      "dom.control": "Control Plane / Python",
      "card.desc.minishell": "A POSIX-style command interpreter written in C, with tokenization, expansion, pipelines, redirections, heredocs, built-ins and interactive signal handling modeled on Bash.",
      "card.desc.philosophers": "A Dining Philosophers simulation using POSIX threads, ordered mutex acquisition and a dedicated observer for timing and termination.",
      "card.desc.minitalk": "An inter-process communication program that sends strings bit by bit through UNIX signals, using acknowledgements to coordinate delivery.",
      "card.desc.myirc": "A multi-client IRC server written in C++98 around non-blocking sockets and poll(), with client buffering, command dispatch and channel management.",
      "card.desc.cpps": "A C++98 exercise suite covering casts and RTTI, templates, STL containers and iterators, plus Ford–Johnson merge-insertion sorting experiments.",
      "card.desc.cub3d": "A software-rendered 2.5D raycaster written in C, using DDA projection, directional texture mapping, map validation and direct framebuffer rendering.",
      "card.desc.fractol": "A real-time Mandelbrot, Julia and Burning Ship explorer with cursor-centered zoom, panning and per-pixel escape-time rendering.",
      "card.desc.inception": "An isolated Docker Compose stack built from Debian-based images, with Nginx TLS termination, WordPress/PHP-FPM, MariaDB, private service networking and file-mounted secrets.",
      "card.desc.gransense": "Full-stack product MVP: FastAPI backend, React/Vite frontend and REST API design, deployed end to end on Vercel with docs and quickstart tooling.",
      "card.desc.harness": "Agent orchestration harness for bug-bounty workflows: recon pipelines, MCP servers, RAG context, prompt/steering systems and systemd-served gateway tooling.",
      "card.desc.ult": "Specification-driven control plane for a multi-agent security harness: budgeting, egress compliance, triage, model routing and memory/RAG integration over FastAPI.",
      "card.ev.minishell": `<span>Owned:</span> lexer, expansion, process execution and signal-state handling.`,
      "card.ev.myirc": `<span>Hard part:</span> handling partial TCP reads without treating recv() as a message boundary.`,
      "card.ev.inception": `<span>Built:</span> three Debian images, TLS termination and file-mounted secrets wired through Compose.`,
      "card.ev.gransense": `<span>Owned:</span> the FastAPI edge-simulator backend — server, REST endpoints and data files.`,
      "path.label": "The unexpected path",
      "path.title": `A technical path<br>built through<br><span class="accent">detours.</span>`,
      "path.1": `Construction taught me <span>that plans meet reality</span>.`,
      "path.2": `Retail taught me <span>to decide while things move</span>.`,
      "path.3": `1337 forced me close to <span>processes, memory and networks</span>.`,
      "path.4": `Leaving it forced me to <span>choose my own direction</span>.`,
      "path.5": `Now I'm consolidating the foundation and building in public.`,
      "exp.label": "03 — Experience",
      "exp.title": `Work before software<br>still shapes <span class="accent">how I build.</span>`,
      "exp.role.1": "Construction Site Manager",
      "exp.role.2": "Store Manager",
      "exp.role.3": "Software Engineering Curriculum",
      "exp.desc.1": "Supervised construction projects from groundwork to delivery, coordinating site teams, subcontractors, logistics, safety, budgets and client relationships.",
      "exp.desc.2": "Managed daily store operations at a delivery startup, coordinating teams, inventory, logistics and customer experience.",
      "exp.desc.3": "Worked through low-level C and C++ projects covering processes, threads, networking, graphics and container infrastructure before leaving the cursus without completing it.",
      "exp.tag.pm": "Project Management",
      "exp.tag.negotiation": "Negotiation",
      "exp.tag.operations": "Operations",
      "exp.tag.team": "Team Coordination",
      "exp.tag.logistics": "Logistics",
      "exp.tag.organization": "Organization",
      "exp.tag.custexp": "Customer Experience",
      "edu.label": "04 — Education",
      "edu.sr": "Education",
      "edu.degree": "Software engineering curriculum — not completed",
      "edu.note": "Coursework and projects in C, C++98, UNIX processes, concurrency, networking, graphics and container infrastructure.",
      "edu.alxDegree": "Backend development coursework",
      "skills.label": "Capabilities",
      "skills.title": `Tools I can<br>work with`,
      "skills.cat1": "Foundations",
      "skills.cat2": "Working knowledge",
      "skills.cat3": "Exploring now",
      "skills.items1": "C · C++98 · Linux · processes · file descriptors · sockets · pthreads",
      "skills.items3": "Modern C++ · embedded Linux · MQTT/IoT · security automation · LLM agents",
      "building.label": "Current direction",
      "building.lead": "Rebuilding depth after a broad two-year sprint: modern C++, Linux networking, embedded/IoT foundations and security automation.",
      "building.strong": "Active experiments",
      "building.card": `Maintaining an <a href="https://github.com/On-Off-Grid/harness" target="_blank" rel="noopener noreferrer">agent-assisted bug-bounty harness</a> and a <a href="https://github.com/On-Off-Grid/Ult_harness" target="_blank" rel="noopener noreferrer">control plane for model routing, budgets, egress policy and memory</a>. These are experiments in orchestration and software design — not claims of autonomous security expertise.`,
      "building.extra": `I'm also revisiting <a href="https://github.com/On-Off-Grid/IgranSense_MVP" target="_blank" rel="noopener noreferrer">IgranSense</a> as a practical bridge between software, sensors and agriculture.`,
      "phil.label": "Personal philosophy",
      "phil.q1": "I would rather",
      "phil.q2": "show unfinished",
      "phil.q3": "understanding than",
      "phil.q4": "borrow the appearance",
      "phil.q5": "of expertise.",
      "phil.note": "My work crosses low-level code, operations and AI-assisted systems. The common thread is not mastery; it is learning how the layers connect and being explicit about what I did, what an agent did, and what still needs work.",
      "contact.title": `If the work<br>is relevant,<br><span class="accent">write.</span>`,
      "contact.note": "I'm open to internships and collaborations around systems, networking, embedded/IoT, developer tooling and security automation. No ceremony needed — mention what you are building and where help is useful.",
      "contact.cta": "View GitHub",
      "footer.tagline": "Systems learner · Software builder · Salé, Morocco",
      "footer.location": "Salé, Morocco",
      "blog.title": "Blog — coming soon",
      "blog.aria": "Blog (coming soon)",
      "doc.title": "Souhail Ouichou — Systems Learner & Software Builder",
      "doc.desc": "Portfolio of Souhail Ouichou, a Morocco-based software builder exploring C, C++, Linux systems, networking, embedded IoT, security tooling, and LLM-agent orchestration."
    },
    fr: {
      "skip": "Aller au contenu",
      "cursor.view": "VOIR",
      "logo.aria": "Souhail Ouichou — accueil",
      "nav.status": `<span class="nav__pulse" aria-hidden="true"></span>Ouvert aux opportunités`,
      "nav.primary": "Principale",
      "nav.mobile": "Mobile",
      "nav.work": `<span>01</span>Travail`,
      "nav.about": `<span>02</span>À propos`,
      "nav.path": `<span>03</span>Parcours`,
      "nav.exp": `<span>04</span>Expérience`,
      "nav.contact": `<span>05</span>Contact`,
      "theme.title": "Basculer clair / sombre",
      "theme.toLight": "Passer au thème clair",
      "theme.toDark": "Passer au thème sombre",
      "menu.open": "Ouvrir le menu",
      "menu.close": "Fermer le menu",
      "lang.toFr": "Passer en français",
      "lang.toEn": "Passer en anglais",
      "portrait.alt": "Portrait de Souhail Ouichou portant une casquette et des lunettes",
      "hero.eyebrow": `C &amp; C++ <span>·</span> Systèmes <span>·</span> Réseaux <span>·</span> Agents`,
      "hero.l1": "Apprendre",
      "hero.l2": "les bases,",
      "hero.l3": "de bas",
      "hero.l4": `en haut<span class="accent">.</span>`,
      "hero.lede": "Je suis Souhail, constructeur de logiciels basé au Maroc. J'ai appris les fondations à travers le C, le C++, Linux, les processus, les sockets et les conteneurs ; j'étends aujourd'hui cette base vers les systèmes embarqués, les outils de sécurité et les harnais d'agents LLM. C'est le récit de ce que j'ai construit, de ce que je comprends, et de ce que je cherche encore à comprendre.",
      "hero.cta": "Voir mes projets",
      "hero.scroll": "Défiler pour explorer",
      "github.aria": "Voir le profil GitHub de Souhail Ouichou",
      "marquee.words": `C <em>·</em> C++ <em>·</em> Linux <em>·</em> Processus <em>·</em> Threads <em>·</em> Réseaux <em>·</em> Systèmes embarqués <em>·</em> Outils de sécurité <em>·</em> Agents LLM <em>·</em> IoT <em>·</em> `,
      "statement.label": "01 — Profil",
      "statement.title": `Du chantier au logiciel :<br>des magasins et des<br>chemins inachevés—<br>pas une carrière linéaire.`,
      "statement.note": `Ces environnements m'ont appris à <span>coordonner les personnes</span>, <span>repérer les défaillances</span> et <span>m'adapter sous pression</span>.`,
      "about.label": "À propos",
      "about.lead": "Je suis Souhail Ouichou, basé au Maroc. Avant le logiciel, j'ai travaillé dans le bâtiment et le commerce de détail, là où les plans rencontrent les retards, les ressources limitées et de vraies personnes.",
      "about.p2": "Ce parcours façonne encore ma manière de construire : inspecter le système, trouver la contrainte, communiquer clairement, et faire fonctionner la prochaine chose utile. Ma base technique est modeste mais réelle : C, C++, Linux, processus, threads, sockets et Docker.",
      "about.p3": "Plus récemment, j'explore les agents LLM, l'orchestration et l'automatisation de sécurité — parfois en écrivant l'implémentation moi-même, parfois en guidant des agents par des spécifications, des tests et des revues.",
      "about.p4": "J'ai quitté 1337 sans terminer le cursus. L'expérience m'a quand même donné des projets difficiles et un goût plus marqué pour le travail honnête plutôt que pour les apparences empruntées. Je consolide aujourd'hui ces fondations, je construis en indépendant, et je cherche un stage où la curiosité, la responsabilité et l'apprentissage visibles comptent.",
      "projects.label": "02 — Projets sélectionnés",
      "projects.title": `Construits à la<br>main, et avec<br><span class="accent">des agents.</span>`,
      "projects.byHand": "Construit à la main",
      "projects.byHandNote": "Projets de cursus et projets personnels où j'ai écrit et débogué l'implémentation moi-même.",
      "projects.byHandContext": "La plupart ont été implémentés pendant le cursus 42/1337, sous contraintes C99, C++98 et bibliothèques restreintes.",
      "projects.withAgents": "Construit avec des agents",
      "projects.withAgentsNote": "J'ai assuré le cadrage du problème, l'architecture, les spécifications, la revue et l'itération ; des agents LLM ont produit l'essentiel de l'implémentation. Les notes des dépôts expliquent la répartition du travail.",
      "card.featured": "Phare",
      "card.viewGithub": "Voir sur GitHub",
      "aria.minishell": "Voir minishell sur GitHub",
      "aria.philosophers": "Voir philosophers sur GitHub",
      "aria.minitalk": "Voir minitalk sur GitHub",
      "aria.myirc": "Voir my_irc sur GitHub",
      "aria.cpps": "Voir CPPS sur GitHub",
      "aria.cub3d": "Voir cub3d sur GitHub",
      "aria.fractol": "Voir fractol sur GitHub",
      "aria.inception": "Voir inception sur GitHub",
      "aria.gransense": "Voir IgranSense MVP sur GitHub",
      "aria.harness": "Voir le harnais bug-bounty sur GitHub",
      "aria.ult": "Voir Ult Harness sur GitHub",
      "dom.systems": "Systèmes / C",
      "dom.concurrency": "Concurrence / C",
      "dom.networking": "Réseaux / C++",
      "dom.oop": "POO / C++",
      "dom.graphics": "Graphisme / C",
      "dom.fullstack": "Full-stack / IA",
      "dom.agents": "Agents / Sécurité",
      "dom.control": "Plan de contrôle / Python",
      "card.desc.minishell": "Un interpréteur de commandes de style POSIX écrit en C, avec tokenisation, expansion, pipelines, redirections, heredocs, commandes intégrées et gestion interactive des signaux, modélisé sur Bash.",
      "card.desc.philosophers": "Une simulation des philosophes avec des threads POSIX, une acquisition ordonnée des mutex et un observateur dédié au chronométrage et à l'arrêt.",
      "card.desc.minitalk": "Un programme de communication inter-processus qui envoie des chaînes bit par bit via des signaux UNIX, en utilisant des accusés de réception pour coordonner la livraison.",
      "card.desc.myirc": "Un serveur IRC multi-client écrit en C++98 autour de sockets non bloquants et poll(), avec tamponnement client, dispatch des commandes et gestion des canaux.",
      "card.desc.cpps": "Une suite d'exercices C++98 couvrant casts et RTTI, templates, conteneurs et itérateurs STL, plus des expériences de tri merge-insertion Ford–Johnson.",
      "card.desc.cub3d": "Un raycaster 2.5D rendu par logiciel, écrit en C, avec projection DDA, texturation directionnelle, validation de carte et rendu direct sur framebuffer.",
      "card.desc.fractol": "Un explorateur Mandelbrot, Julia et Burning Ship en temps réel avec zoom centré sur le curseur, déplacement et rendu du temps d'échappement par pixel.",
      "card.desc.inception": "Une pile Docker Compose isolée construite à partir d'images Debian, avec terminaison TLS Nginx, WordPress/PHP-FPM, MariaDB, réseau de services privé et secrets montés en fichiers.",
      "card.desc.gransense": "MVP produit full-stack : backend FastAPI, frontend React/Vite et conception d'API REST, déployé de bout en bout sur Vercel avec documentation et outils de démarrage rapide.",
      "card.desc.harness": "Harnais d'orchestration d'agents pour des flux bug-bounty : pipelines de recon, serveurs MCP, contexte RAG, systèmes de prompt et de pilotage, et outils de passerelle servis par systemd.",
      "card.desc.ult": "Plan de contrôle piloté par spécifications pour un harnais de sécurité multi-agents : budgets, conformité egress, triage, routage de modèles et intégration mémoire/RAG sur FastAPI.",
      "card.ev.minishell": `<span>Ma part :</span> lexer, expansion, exécution des processus et gestion de l'état des signaux.`,
      "card.ev.myirc": `<span>Le point délicat :</span> gérer les lectures TCP partielles sans traiter recv() comme une limite de message.`,
      "card.ev.inception": `<span>Construit :</span> trois images Debian, terminaison TLS et secrets montés en fichiers, câblés via Compose.`,
      "card.ev.gransense": `<span>Ma part :</span> le backend simulateur d'edges FastAPI — serveur, endpoints REST et fichiers de données.`,
      "path.label": "Le chemin inattendu",
      "path.title": `Un parcours<br>technique,<br>construit par<br><span class="accent">des détours.</span>`,
      "path.1": `Le bâtiment m'a appris <span>que les plans rencontrent la réalité</span>.`,
      "path.2": `Le commerce m'a appris <span>à décider pendant que tout bouge</span>.`,
      "path.3": `1337 m'a confronté de près aux <span>processus, à la mémoire et aux réseaux</span>.`,
      "path.4": `En partir m'a obligé à <span>choisir ma propre direction</span>.`,
      "path.5": `Aujourd'hui je consolide la fondation et je construis en public.`,
      "exp.label": "03 — Expérience",
      "exp.title": `L'ancien métier<br>façonne<br><span class="accent">comment je<br>construis.</span>`,
      "exp.role.1": "Chef de chantier",
      "exp.role.2": "Responsable de magasin",
      "exp.role.3": "Parcours d'ingénierie logicielle",
      "exp.desc.1": "Supervision de projets de construction du terrassement à la livraison, en coordonnant équipes de chantier, sous-traitants, logistique, sécurité, budgets et relations clients.",
      "exp.desc.2": "Gestion quotidienne des opérations d'un magasin de livraison, en coordonnant équipes, stocks, logistique et expérience client.",
      "exp.desc.3": "Réalisation de projets C et C++ bas niveau couvrant processus, threads, réseaux, graphisme et infrastructure de conteneurs, avant de quitter le cursus sans le terminer.",
      "exp.tag.pm": "Gestion de projet",
      "exp.tag.negotiation": "Négociation",
      "exp.tag.operations": "Opérations",
      "exp.tag.team": "Coordination d'équipe",
      "exp.tag.logistics": "Logistique",
      "exp.tag.organization": "Organisation",
      "exp.tag.custexp": "Expérience client",
      "edu.label": "04 — Formation",
      "edu.sr": "Formation",
      "edu.degree": "Parcours d'ingénierie logicielle — non terminé",
      "edu.note": "Cours et projets en C, C++98, processus UNIX, concurrence, réseaux, graphisme et infrastructure de conteneurs.",
      "edu.alxDegree": "Cours de développement backend",
      "skills.label": "Compétences",
      "skills.title": `Des outils<br>que je sais<br>utiliser`,
      "skills.cat1": "Fondations",
      "skills.cat2": "Connaissances pratiques",
      "skills.cat3": "Explorations en cours",
      "skills.items1": "C · C++98 · Linux · processus · descripteurs de fichiers · sockets · pthreads",
      "skills.items3": "C++ moderne · Linux embarqué · MQTT/IoT · automatisation de sécurité · agents LLM",
      "building.label": "Direction actuelle",
      "building.lead": "Reconstruction de la profondeur après un sprint large de deux ans : C++ moderne, réseaux Linux, fondations embarquées/IoT et automatisation de sécurité.",
      "building.strong": "Expériences actives",
      "building.card": `Entretien d'un <a href="https://github.com/On-Off-Grid/harness" target="_blank" rel="noopener noreferrer">harnais de bug-bounty assisté par agents</a> et d'un <a href="https://github.com/On-Off-Grid/Ult_harness" target="_blank" rel="noopener noreferrer">plan de contrôle pour le routage de modèles, les budgets, la politique egress et la mémoire</a>. Ce sont des expériences d'orchestration et de conception logicielle — pas des prétentions d'expertise en sécurité autonome.`,
      "building.extra": `Je revisite aussi <a href="https://github.com/On-Off-Grid/IgranSense_MVP" target="_blank" rel="noopener noreferrer">IgranSense</a> comme pont pratique entre logiciel, capteurs et agriculture.`,
      "phil.label": "Philosophie personnelle",
      "phil.q1": "Mieux vaut une",
      "phil.q2": "compréhension",
      "phil.q3": "inachevée",
      "phil.q4": "que de feindre",
      "phil.q5": "l'expertise.",
      "phil.note": "Mon travail traverse le code bas niveau, l'exploitation et les systèmes assistés par IA. Le fil conducteur n'est pas la maîtrise ; c'est d'apprendre comment les couches se connectent et d'être explicite sur ce que j'ai fait, ce qu'un agent a fait, et ce qui reste à travailler.",
      "contact.title": `Si le travail<br>vous parle,<br><span class="accent">écrivez.</span>`,
      "contact.note": "Ouvert aux stages et aux collaborations autour des systèmes, des réseaux, de l'embarqué/IoT, des outils pour développeurs et de l'automatisation de sécurité. Pas de cérémonie — dites-moi ce que vous construisez et où un coup de main est utile.",
      "contact.cta": "Voir sur GitHub",
      "footer.tagline": "Apprenant des systèmes · Constructeur de logiciels · Salé, Maroc",
      "footer.location": "Salé, Maroc",
      "blog.title": "Blog — bientôt disponible",
      "blog.aria": "Blog (bientôt disponible)",
      "doc.title": "Souhail Ouichou — Apprenant de systèmes & constructeur de logiciels",
      "doc.desc": "Portfolio de Souhail Ouichou, constructeur de logiciels basé au Maroc, explorant le C, le C++, les systèmes Linux, les réseaux, l'IoT embarqué, les outils de sécurité et l'orchestration d'agents LLM."
    }
  };

  var DEFAULT = "en";
  var current = DEFAULT;

  /* ----------------------------------------------------------------- helpers */
  function pick() {
    var lang = null;
    try { lang = new URLSearchParams(location.search).get("lang"); } catch (e) { /* noop */ }
    if (lang !== "fr" && lang !== "en") {
      try { lang = localStorage.getItem("lang"); } catch (e) { /* private mode */ }
    }
    if (lang !== "fr" && lang !== "en") {
      var nav = (navigator.languages && navigator.languages.length ? navigator.languages[0] : navigator.language) || "";
      lang = nav.toLowerCase().indexOf("fr") === 0 ? "fr" : DEFAULT;
    }
    return lang;
  }

  function dict(lang) { return I18N[lang] || I18N[DEFAULT]; }

  /* -------------------------------------------------------------------- apply */
  function apply(lang) {
    current = lang;
    var d = dict(lang);
    var root = document.documentElement;

    root.lang = lang;
    root.dataset.lang = lang;

    var i, el;
    var text = document.querySelectorAll("[data-i18n]");
    for (i = 0; i < text.length; i++) {
      el = text[i];
      if (d[el.dataset.i18n] != null) el.textContent = d[el.dataset.i18n];
    }
    var html = document.querySelectorAll("[data-i18n-html]");
    for (i = 0; i < html.length; i++) {
      el = html[i];
      if (d[el.dataset.i18nHtml] != null) el.innerHTML = d[el.dataset.i18nHtml];
    }
    var aria = document.querySelectorAll("[data-i18n-aria]");
    for (i = 0; i < aria.length; i++) {
      el = aria[i];
      if (d[el.dataset.i18nAria] != null) el.setAttribute("aria-label", d[el.dataset.i18nAria]);
    }
    var alt = document.querySelectorAll("[data-i18n-alt]");
    for (i = 0; i < alt.length; i++) {
      el = alt[i];
      if (d[el.dataset.i18nAlt] != null) el.setAttribute("alt", d[el.dataset.i18nAlt]);
    }
    var title = document.querySelectorAll("[data-i18n-title]");
    for (i = 0; i < title.length; i++) {
      el = title[i];
      if (d[el.dataset.i18nTitle] != null) el.setAttribute("title", d[el.dataset.i18nTitle]);
    }

    if (d["doc.title"]) document.title = d["doc.title"];
    var meta = document.querySelector('meta[name="description"]');
    if (meta && d["doc.desc"]) meta.setAttribute("content", d["doc.desc"]);

    /* Language toggle: show the language the click will switch TO */
    var btn = document.getElementById("langToggle");
    if (btn) {
      var target = lang === "fr" ? "lang.toEn" : "lang.toFr";
      btn.textContent = lang === "fr" ? "EN" : "FR";
      btn.setAttribute("aria-label", d[target] || "");
      btn.setAttribute("title", d[target] || "");
    }

    document.dispatchEvent(new CustomEvent("i18n:applied", { detail: { lang: lang } }));
  }

  function setLang(lang) {
    if (lang !== "fr" && lang !== "en") return;
    try { localStorage.setItem("lang", lang); } catch (e) { /* private mode */ }
    apply(lang);
  }

  /* -------------------------------------------------------------------- boot */
  window.i18n = {
    t: function (key) { return dict(current)[key] != null ? dict(current)[key] : (I18N[DEFAULT][key] || ""); },
    lang: function () { return current; },
    set: setLang,
    apply: apply
  };

  apply(pick());

  var btn = document.getElementById("langToggle");
  if (btn) {
    btn.addEventListener("click", function () { setLang(current === "fr" ? "en" : "fr"); });
  }
})();

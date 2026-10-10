/* ==========================================================================
   SOUHAIL OUICHOU — PORTFOLIO / script.js
   ========================================================================== */

document.addEventListener("DOMContentLoaded", () => {
  initThemeToggle();
  initNavigation();
  initAnimations();
  initCursor();
  initScrollProgress();
  initMobileMenu();
  initMagneticButtons();

  if (window.lucide) lucide.createIcons();
});

const prefersReducedMotion = window.matchMedia("(prefers-reduced-motion: reduce)").matches;

/* UI strings for stateful labels (theme toggle, menu toggle). They live in
   the i18n.js dictionary; the EN literals are the fallback if that file is
   missing. i18n.js fires "i18n:applied" on every language switch so these
   labels follow along. */
const UI_FALLBACK = {
  "theme.toLight": "Switch to light theme",
  "theme.toDark": "Switch to dark theme",
  "menu.open": "Open menu",
  "menu.close": "Close menu"
};
const uiText = (key) => (window.i18n && window.i18n.t(key)) || UI_FALLBACK[key] || key;

/* THEME (light / dark) -----------------------------------------------------
   The initial data-theme is applied pre-paint by an inline script in <head>
   to avoid a flash. This wires the toggle button + system-preference sync. */
function initThemeToggle() {
  const root = document.documentElement;
  const btn = document.getElementById("themeToggle");
  const meta = document.querySelector('meta[name="theme-color"]');
  const sysLight = window.matchMedia("(prefers-color-scheme: light)");

  const themeColor = () => (root.dataset.theme === "light" ? "#F4F4F0" : "#080808");

  const paint = (theme) => {
    root.dataset.theme = theme;
    if (btn) {
      const toLight = theme !== "light"; /* label = theme the click will switch TO */
      btn.setAttribute("aria-label", uiText(toLight ? "theme.toLight" : "theme.toDark"));
    }
    if (meta) meta.setAttribute("content", themeColor());
  };

  paint(root.dataset.theme || (sysLight.matches ? "light" : "dark"));

  /* Re-label after a language switch (i18n.js) */
  document.addEventListener("i18n:applied", () => {
    if (btn) btn.setAttribute("aria-label", uiText(root.dataset.theme !== "light" ? "theme.toLight" : "theme.toDark"));
  });

  if (btn) {
    btn.addEventListener("click", () => {
      const next = root.dataset.theme === "light" ? "dark" : "light";
      try { localStorage.setItem("theme", next); } catch (e) { /* private mode */ }
      paint(next);
    });
  }

  /* Follow the OS only while the visitor hasn't chosen explicitly */
  const sync = (e) => {
    let saved = null;
    try { saved = localStorage.getItem("theme"); } catch (err) { /* noop */ }
    if (!saved) paint(e.matches ? "light" : "dark");
  };
  if (sysLight.addEventListener) sysLight.addEventListener("change", sync);
  else if (sysLight.addListener) sysLight.addListener(sync);
}

/* NAVIGATION -------------------------------------------------------------- */
function initNavigation() {
  const nav = document.getElementById("nav");
  if (!nav) return;

  const onScroll = () => {
    nav.classList.toggle("is-scrolled", window.scrollY > 40);
  };
  onScroll();
  window.addEventListener("scroll", onScroll, { passive: true });

  const links = Array.from(document.querySelectorAll(".nav__links a"));
  const sections = links
    .map((link) => document.querySelector(link.getAttribute("href")))
    .filter(Boolean);

  if ("IntersectionObserver" in window && sections.length) {
    const observer = new IntersectionObserver(
      (entries) => {
        entries.forEach((entry) => {
          if (!entry.isIntersecting) return;
          links.forEach((link) =>
            link.classList.toggle("is-active", link.getAttribute("href") === "#" + entry.target.id)
          );
        });
      },
      { rootMargin: "-45% 0px -50% 0px", threshold: 0 }
    );
    sections.forEach((section) => observer.observe(section));
  }
}

/* MOBILE MENU ------------------------------------------------------------- */
function initMobileMenu() {
  const menu = document.getElementById("mobileMenu");
  const toggle = document.getElementById("navToggle");
  const close = document.getElementById("menuClose");
  if (!menu || !toggle) return;

  const setOpen = (open) => {
    menu.classList.toggle("is-open", open);
    document.body.classList.toggle("menu-open", open);
    toggle.setAttribute("aria-expanded", String(open));
    toggle.setAttribute("aria-label", uiText(open ? "menu.close" : "menu.open"));
    menu.inert = !open;
    if (open) {
      const first = menu.querySelector("a, button");
      if (first) first.focus();
    } else {
      toggle.focus({ preventScroll: true });
    }
  };

  menu.inert = true;

  /* Follow the active language (i18n.js) */
  document.addEventListener("i18n:applied", () => {
    toggle.setAttribute("aria-label", uiText(menu.classList.contains("is-open") ? "menu.close" : "menu.open"));
  });

  toggle.addEventListener("click", () => setOpen(!menu.classList.contains("is-open")));
  if (close) close.addEventListener("click", () => setOpen(false));

  menu.querySelectorAll("a[href^='#']").forEach((link) => {
    link.addEventListener("click", () => setOpen(false));
  });

  document.addEventListener("keydown", (event) => {
    if (event.key === "Escape" && menu.classList.contains("is-open")) setOpen(false);
  });

  window.addEventListener("resize", () => {
    if (window.innerWidth >= 900 && menu.classList.contains("is-open")) setOpen(false);
  });
}

/* SCROLL PROGRESS --------------------------------------------------------- */
function initScrollProgress() {
  const bar = document.getElementById("progressBar");
  if (!bar) return;

  let ticking = false;

  const update = () => {
    const doc = document.documentElement;
    const max = doc.scrollHeight - window.innerHeight;
    const progress = max > 0 ? window.scrollY / max : 0;
    bar.style.transform = "scaleX(" + Math.min(Math.max(progress, 0), 1) + ")";
    ticking = false;
  };

  window.addEventListener(
    "scroll",
    () => {
      if (!ticking) {
        window.requestAnimationFrame(update);
        ticking = true;
      }
    },
    { passive: true }
  );

  window.addEventListener("resize", update);
  update();
}

/* CURSOR ------------------------------------------------------------------ */
function initCursor() {
  const cursor = document.getElementById("cursor");
  if (!cursor) return;

  const finePointer = window.matchMedia("(pointer: fine)").matches;
  if (!finePointer) return;

  /* Reduced motion: keep the native cursor, no follower ring (CSS leaves
     .cursor at display:none when this returns early) */
  if (prefersReducedMotion) return;

  cursor.style.display = "grid";

  let mouseX = window.innerWidth / 2;
  let mouseY = window.innerHeight / 2;
  let currentX = mouseX;
  let currentY = mouseY;

  document.addEventListener(
    "mousemove",
    (event) => {
      mouseX = event.clientX;
      mouseY = event.clientY;
      cursor.classList.remove("is-hidden");
    },
    { passive: true }
  );

  document.addEventListener("mouseleave", () => cursor.classList.add("is-hidden"));

  const render = () => {
    currentX += (mouseX - currentX) * 0.18;
    currentY += (mouseY - currentY) * 0.18;
    cursor.style.transform = "translate3d(" + currentX + "px," + currentY + "px,0)";
    window.requestAnimationFrame(render);
  };
  render();

  /* Elements that make the cursor grow on hover (.project = work cards) */
  const hoverTargets = document.querySelectorAll("a, button, .tl, .skills__list li, .project");
  hoverTargets.forEach((el) => {
    el.addEventListener("mouseenter", () => {
      if (el.dataset.cursor === "hide") {
        cursor.classList.add("is-hidden");
      } else {
        cursor.classList.add("is-active");
      }
    });
    el.addEventListener("mouseleave", () => {
      cursor.classList.remove("is-active", "is-hidden");
    });
  });
}

/* MAGNETIC BUTTONS -------------------------------------------------------- */
function initMagneticButtons() {
  if (prefersReducedMotion || !window.matchMedia("(pointer: fine)").matches) return;

  document.querySelectorAll(".magnetic").forEach((el) => {
    const strength = 0.22;

    el.addEventListener("mousemove", (event) => {
      const rect = el.getBoundingClientRect();
      const x = (event.clientX - rect.left - rect.width / 2) * strength;
      const y = (event.clientY - rect.top - rect.height / 2) * strength;
      el.style.transform = "translate(" + x + "px," + y + "px)";
    });

    el.addEventListener("mouseleave", () => {
      el.style.transform = "translate(0,0)";
    });
  });
}

/* ANIMATIONS -------------------------------------------------------------- */
function initAnimations() {
  if (prefersReducedMotion || !window.gsap) return;

  gsap.registerPlugin(ScrollTrigger);

  /* Hero intro */
  const heroTl = gsap.timeline({ defaults: { ease: "power3.out" } });

  heroTl
    .from("#nav", { y: -16, autoAlpha: 0, duration: 0.7 })
    .from(".hero__eyebrow", { y: 18, autoAlpha: 0, duration: 0.6 }, "-=0.3")
    .from(".hero__title .line > span", { yPercent: 110, duration: 0.9, stagger: 0.09 }, "-=0.35")
    .from(".hero__accent-line", { scaleX: 0, duration: 0.8, transformOrigin: "0 50%" }, "-=0.45")
    .from(".hero__lede", { y: 20, autoAlpha: 0, duration: 0.7 }, "-=0.55")
    .from(".hero__actions .btn", { y: 18, autoAlpha: 0, duration: 0.6, stagger: 0.1 }, "-=0.45")
    .from(".portrait__frame", { y: 60, autoAlpha: 0, duration: 1 }, "-=0.95")
    .from(".portrait__caption", { autoAlpha: 0, duration: 0.5 }, "-=0.35")
    .from(".hero__scroll", { autoAlpha: 0, y: 12, duration: 0.6 }, "-=0.3");

  /* Generic reveals */
  gsap.utils.toArray("[data-reveal]").forEach((el) => {
    gsap.from(el, {
      y: 38,
      autoAlpha: 0,
      duration: 0.9,
      ease: "power3.out",
      scrollTrigger: { trigger: el, start: "top 88%" }
    });
  });

  /* Unexpected path — progressive reveal */
  gsap.from(".path__item", {
    y: 40,
    autoAlpha: 0,
    duration: 0.85,
    stagger: 0.14,
    ease: "power3.out",
    scrollTrigger: { trigger: ".path__list", start: "top 80%" }
  });

  /* Experience timeline line */
  const timelineFill = document.getElementById("timelineFill");
  if (timelineFill) {
    gsap.fromTo(
      timelineFill,
      { scaleY: 0 },
      {
        scaleY: 1,
        ease: "none",
        scrollTrigger: {
          trigger: ".timeline",
          start: "top 75%",
          end: "bottom 70%",
          scrub: 0.4
        }
      }
    );
  }

  /* Skills rows */
  gsap.from(".skills__list li", {
    y: 30,
    autoAlpha: 0,
    duration: 0.7,
    stagger: 0.07,
    ease: "power3.out",
    scrollTrigger: { trigger: ".skills__list", start: "top 82%" }
  });

  /* Philosophy quote */
  gsap.from(".phil__quote .line > span", {
    yPercent: 110,
    duration: 0.95,
    stagger: 0.1,
    ease: "power4.out",
    scrollTrigger: { trigger: ".phil__quote", start: "top 78%" }
  });

  /* Ghost number parallax */
  const ghost = document.querySelector(".edu__ghost");
  if (ghost) {
    gsap.to(ghost, {
      yPercent: -12,
      ease: "none",
      scrollTrigger: { trigger: ".edu__feature", start: "top bottom", end: "bottom top", scrub: true }
    });
  }

  window.addEventListener("load", () => ScrollTrigger.refresh());
}

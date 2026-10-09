/* ==========================================================================
   SOUHAIL OUICHOU — PORTFOLIO / script.js
   ========================================================================== */

document.addEventListener("DOMContentLoaded", () => {
  initNavigation();
  initAnimations();
  initCursor();
  initScrollProgress();
  initMobileMenu();
  initMagneticButtons();

  if (window.lucide) lucide.createIcons();
});

const prefersReducedMotion = window.matchMedia("(prefers-reduced-motion: reduce)").matches;

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
    toggle.setAttribute("aria-label", open ? "Close menu" : "Open menu");
    menu.inert = !open;
    if (open) {
      const first = menu.querySelector("a, button");
      if (first) first.focus();
    } else {
      toggle.focus({ preventScroll: true });
    }
  };

  menu.inert = true;

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

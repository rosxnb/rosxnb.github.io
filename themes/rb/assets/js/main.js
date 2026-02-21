// ─── RB Theme — main.js ───────────────────────────────────────────────────────

// ─── Theme toggle (runs before DOMContentLoaded to prevent flash) ──────────────
(function () {
  var STORAGE_KEY = 'rb-theme';
  var html = document.documentElement;

  function getPreferred() {
    var stored = localStorage.getItem(STORAGE_KEY);
    if (stored) return stored;
    return window.matchMedia('(prefers-color-scheme: dark)').matches ? 'dark' : 'light';
  }

  function applyTheme(theme) {
    html.setAttribute('data-theme', theme);
    localStorage.setItem(STORAGE_KEY, theme);
  }

  applyTheme(getPreferred());

  document.addEventListener('DOMContentLoaded', function () {
    var btn = document.getElementById('themeToggle');
    if (!btn) return;
    btn.addEventListener('click', function () {
      var current = html.getAttribute('data-theme');
      applyTheme(current === 'dark' ? 'light' : 'dark');
    });
  });
})();

// ─── Mobile sidebar ────────────────────────────────────────────────────────────
document.addEventListener('DOMContentLoaded', function () {
  var sidebar = document.getElementById('sidebar');
  var overlay = document.getElementById('sidebarOverlay');
  var btn = document.getElementById('mobileSidebarBtn');
  if (!sidebar || !overlay || !btn) return;

  function openSidebar() {
    sidebar.classList.add('is-open');
    overlay.classList.add('is-open');
    btn.setAttribute('aria-expanded', 'true');
  }
  function closeSidebar() {
    sidebar.classList.remove('is-open');
    overlay.classList.remove('is-open');
    btn.setAttribute('aria-expanded', 'false');
  }

  btn.addEventListener('click', function () {
    sidebar.classList.contains('is-open') ? closeSidebar() : openSidebar();
  });
  overlay.addEventListener('click', closeSidebar);
});

// ─── TOC: active link + reading progress ──────────────────────────────────────
document.addEventListener('DOMContentLoaded', function () {
  var tocNav = document.getElementById('tocNav');
  var progressBar = document.getElementById('tocProgressBar');
  if (!tocNav) return;

  var tocLinks = Array.from(tocNav.querySelectorAll('a'));
  if (!tocLinks.length) return;

  var headings = tocLinks
    .map(function (a) { return document.getElementById(a.getAttribute('href').slice(1)); })
    .filter(Boolean);

  function updateTOC() {
    var scrollY = window.scrollY;
    var docH = document.documentElement.scrollHeight - window.innerHeight;
    var pct = docH > 0 ? Math.min((scrollY / docH) * 100, 100) : 0;
    if (progressBar) progressBar.style.width = pct.toFixed(1) + '%';

    var current = headings[0];
    var offset = 80;
    for (var i = 0; i < headings.length; i++) {
      if (headings[i].getBoundingClientRect().top - offset < 0) current = headings[i];
    }
    tocLinks.forEach(function (link) {
      link.classList.toggle('active', !!(current && link.getAttribute('href') === '#' + current.id));
    });
  }

  window.addEventListener('scroll', updateTOC, { passive: true });
  updateTOC();
});

// ─── Code copy buttons ─────────────────────────────────────────────────────────
document.addEventListener('DOMContentLoaded', function () {
  document.querySelectorAll('.highlight').forEach(function (block) {
    var pre = block.querySelector('pre');
    if (!pre) return;

    // Try to detect language
    var lang = '';
    var codeEl = pre.querySelector('code');
    if (codeEl) {
      var m = codeEl.className.match(/language-(\w+)/);
      if (m) lang = m[1];
    }
    if (!lang) {
      var m2 = block.className.match(/language-(\w+)/);
      if (m2) lang = m2[1];
    }

    var wrapper = document.createElement('div');
    wrapper.className = 'code-wrapper';

    var header = document.createElement('div');
    header.className = 'code-header';

    var langLabel = document.createElement('span');
    langLabel.className = 'code-lang';
    langLabel.textContent = lang || 'code';

    var copyBtn = document.createElement('button');
    copyBtn.className = 'code-copy-btn';
    copyBtn.textContent = 'Copy';
    copyBtn.setAttribute('aria-label', 'Copy code to clipboard');

    copyBtn.addEventListener('click', function () {
      var text = pre.innerText || pre.textContent || '';
      navigator.clipboard.writeText(text).then(function () {
        copyBtn.textContent = 'Copied!';
        copyBtn.classList.add('copied');
        setTimeout(function () {
          copyBtn.textContent = 'Copy';
          copyBtn.classList.remove('copied');
        }, 2000);
      }).catch(function () {
        copyBtn.textContent = 'Error';
        setTimeout(function () { copyBtn.textContent = 'Copy'; }, 2000);
      });
    });

    header.appendChild(langLabel);
    header.appendChild(copyBtn);
    wrapper.appendChild(header);

    block.parentNode.insertBefore(wrapper, block);
    wrapper.appendChild(block);
  });
});

// ─── Search overlay ────────────────────────────────────────────────────────────
document.addEventListener('DOMContentLoaded', function () {
  var overlay   = document.getElementById('searchOverlay');
  var trigger   = document.getElementById('searchTrigger');
  if (!overlay) return;

  var pagefindInitialised = false;

  function openSearch() {
    overlay.classList.add('is-open');
    overlay.setAttribute('aria-hidden', 'false');
    document.body.style.overflow = 'hidden';

    // Initialise Pagefind UI once
    if (!pagefindInitialised && window.PagefindUI) {
      new PagefindUI({
        element: '#search',
        showSubResults: true,
        showImages: false,
        resetStyles: false,
      });
      pagefindInitialised = true;
    }

    // Auto-focus the input after short delay (lets animation settle)
    setTimeout(function () {
      var input = overlay.querySelector('.pagefind-ui__search-input');
      if (input) input.focus();
    }, 50);
  }

  function closeSearch() {
    overlay.classList.remove('is-open');
    overlay.setAttribute('aria-hidden', 'true');
    document.body.style.overflow = '';
  }

  // Open on "/" keypress (unless user is typing in an input)
  document.addEventListener('keydown', function (e) {
    if (e.key === '/' && !['INPUT', 'TEXTAREA'].includes(document.activeElement.tagName)) {
      e.preventDefault();
      openSearch();
    }
    if (e.key === 'Escape') {
      closeSearch();
    }
  });

  if (trigger) trigger.addEventListener('click', openSearch);

  // Click outside modal to close
  overlay.addEventListener('click', function (e) {
    if (e.target === overlay) closeSearch();
  });
});

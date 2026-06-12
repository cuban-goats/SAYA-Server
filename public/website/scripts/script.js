const btn = document.getElementById('fancyBtn');

btn.addEventListener('click', function (e) {
  // Ripple effect
  const ripple = document.createElement('span');
  ripple.classList.add('ripple');
  const rect = btn.getBoundingClientRect();
  const size = Math.max(rect.width, rect.height);
  ripple.style.width = ripple.style.height = size + 'px';
  ripple.style.left = (e.clientX - rect.left - size / 2) + 'px';
  ripple.style.top = (e.clientY - rect.top - size / 2) + 'px';
  btn.appendChild(ripple);
  ripple.addEventListener('animationend', () => ripple.remove());

  // Pop animation
  btn.classList.remove('pop');
  void btn.offsetWidth; // reflow to restart animation
  btn.classList.add('pop');
});

const prefixes = 'fapnum kMGTPE'.split('');
export function human({ value, unit = 'bytes' }) {
  let sign = Math.sign(value);
  let exponentDiv = 0;
  let root = Math.abs(value);
  let m = root;
  if (root >= 1) {
    while (m >= 1000) {
      m = m / 1000;
      exponentDiv += 1;
    }
    /*m=m*1000;
    exponentDiv-=1*/
  } else {
    while (m < 1000) {
      m = m * 1000;
      exponentDiv -= 1;
    }
    m = m / 1000;
    exponentDiv += 1;
  }
  const prefix = prefixes[exponentDiv + 6];
  return `${m.toFixed(1 + (m % 3))}${prefix}${unit}`; //`${value.toFixed(1)}${root.toFixed(0)}${prefix}${unit}`; //`${sign}${(absValue / normalizerValue).toFixed(2) + prefix + unit}`;
}
export function humanTime({ value, unit = 's' }) {}

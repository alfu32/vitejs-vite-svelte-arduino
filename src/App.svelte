<script>
  import viteLogo from '/vite.svg'
  import svelteLogo from './assets/svelte.svg'
  import Counter from './lib/Counter.svelte'
  import PwmController from './lib/PwmController.svelte'
  import AnalogInput from './lib/AnalogInput.svelte'
</script>

<main>
  <AnalogInput id="A0"/>
  <PwmController id="D0"/>
  <PwmController id="D1"/>
  <PwmController id="D2"/>
  <PwmController id="D3"/>
  <PwmController id="D4"/>
  <PwmController id="D5"/>
  <PwmController id="D6"/>
  <PwmController id="D7"/>
  <PwmController id="D8"/>
</main>

<style>
</style>

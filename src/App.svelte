<script>
  import viteLogo from '/vite.svg'
  import svelteLogo from './assets/svelte.svg'
  import PwmController from './lib/PwmController.svelte'
  import AnalogInput from './lib/AnalogInput.svelte'
  import DigitalInput from './lib/DigitalInput.svelte'
</script>

<main>
  <AnalogInput id="A0"/>
  <PwmController id="D0"/>
  <PwmController id="D1"/>
  <PwmController id="D2"/>
  <PwmController id="D3"/>
  <PwmController id="D4"/>
  <PwmController id="D5"/>
  <DigitalInput id="D6"/>
  <DigitalInput id="D7"/>
  <DigitalInput id="D8"/>
</main>

<style>
</style>

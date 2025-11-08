<script>
	import Pill from "./Pill.svelte"
	import { SvelteSet } from "svelte/reactivity"

	const items = $state(['red', 'blue', 'orange']);

	function handleClick(index) {
		items.splice(index, 1);
	}

	function handleAddClicked() {
		items.push("new color")
	}
</script>

<div class="space-y-3 w-1/2">
	<ul class="flex flex-wrap gap-2 bg-gray-200">
		{#each items as item, i}
			<li>
				<Pill color={item} >
					{#snippet content(color)}
						<div class="flex py-1 px-2 gap-2">
						  <div class="flex gap-2 justify-center items-center">
								{#key color}
									<!-- IMPORTANT to key on color, otherwise svelte tries to re-use exisint div with style -->
									<div style:background-color={color} class="size-3 rounded-full bg-white"></div>
								{/key}
						    <input
									class="text-center w-30 truncate"
								  type="text"
									bind:value={items[i]}
								/>
						  </div>
						  <button
								class="bg-gray-500 rounded-full size-6 text-white cursor-pointer"
								onclick={() => handleClick(i)}
							>
						    X
						  </button>
						</div>
					{/snippet}
				</Pill>
			</li>
		{/each}
		<button
			class="bg-gray-300 rounded-full flex items-center justify-center size-8 cursor-pointer"
			onclick={handleAddClicked}
		>
			+
		</button>
	</ul>
</div>

<script>
	const {
		color,
		content = textContent,
		...extra
	} = $props();
	
</script>

{#snippet textContent(color)}
	<span>#{color}</span>
{/snippet}

<div class="rounded-full bg-gray-400">
	{@render content(color, extra)}
</div>
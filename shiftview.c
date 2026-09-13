/** Function to shift the current view to the left/right
 *
 * @param: "arg->i" stores the number of tags to shift right (positive value)
 *          or left (negative value)
 */
static unsigned int
shifttags(unsigned int tagset, int shift)
{
	int n = LENGTH(tags);

	shift %= n;
	if (shift < 0)
		shift += n;
	if (!shift)
		return tagset & TAGMASK;
	return ((tagset << shift) | (tagset >> (n - shift))) & TAGMASK;
}

void
shiftview(const Arg *arg)
{
	Arg a;
	Client *c;
	unsigned visible = 0;
	int i = arg->i;
	int count = 0;
	unsigned int nextseltags, curseltags = selmon->tagset[selmon->seltags];

	do {
		nextseltags = shifttags(curseltags, i);

		// Check if tag is visible
		for (c = selmon->clients; c && !visible; c = c->next)
			if (nextseltags & c->tags) {
				visible = 1;
				break;
			}
		i += arg->i;
	} while (!visible && ++count < 10);

	if (count < 10) {
		a.ui = nextseltags;
		view(&a);
	}
}

void
shifttag(const Arg *arg)
{
	Arg a;
	Client *c;
	unsigned visible = 0;
	int i = arg->i;
	int count = 0;
	unsigned int nextseltags, curseltags = selmon->tagset[selmon->seltags];

	do {
		nextseltags = shifttags(curseltags, i);

		// Check if tag is visible
		for (c = selmon->clients; c && !visible; c = c->next)
			if (nextseltags & c->tags) {
				visible = 1;
				break;
			}
		i += arg->i;
	} while (!visible && ++count < 10);

	if (count < 10) {
		a.ui = nextseltags;
		tag(&a);
	}
}

import * as React from "react";

import Button from "@material-ui/core/Button";
import Typography from "@material-ui/core/Typography";
import Grid from "@material-ui/core/Grid";

export class MuiButtons extends React.Component {
    render() {
        return (
            <Grid container spacing={0}>
                <Grid item xs={12}>
                    <Typography>Text</Typography>
                    <Button color="default" variant="text">Default</Button>
                    <Button color="primary" variant="text">Primary</Button>
                    <Button color="secondary" variant="text">Secondary</Button>
                </Grid>
                <Grid item xs={12}>
                    <Typography>Contained</Typography>
                    <Button color="default" variant="contained">Default</Button>
                    <Button color="primary" variant="contained">Primary</Button>
                    <Button color="secondary" variant="contained">Secondary</Button>
                </Grid>
                <Grid item xs={12}>
                    <Typography>Outlined</Typography>
                    <Button color="default" variant="outlined">Default</Button>
                    <Button color="primary" variant="outlined">Primary</Button>
                    <Button color="secondary" variant="outlined">Secondary</Button>
                </Grid>
            </Grid>
        );
    }
}

import React from 'react';
import { Button, Header } from 'semantic-ui-react'

const Home = ({
  doorStatus,
  openDoor,
  closeDoor,
}) => {
  return (
    <div>
      <Header size='huge'>IofT Adventure</Header>
      <p>The door is currently : {doorStatus}</p>
      <Header size='medium'>What would you like to do with the door ?</Header>
      <Button
        inverted
        color='green'
        onClick={ () => { openDoor() }}
      >
        Open
      </Button>
      <Button
        inverted
        color='red'
        onClick={ () => { closeDoor() }}
      >
        Close
      </Button>
    </div>
  );
};

export default Home;

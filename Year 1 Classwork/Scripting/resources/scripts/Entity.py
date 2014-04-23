import AIE
import game
import Level_Grid
import math
import random

#Tank Entity
#   A simple entity that can be placed on the screen with a right click, you should modify this so that the tank can be told to 
#   navigate to a point instead of instantly move.

class TankEntity:

	def __init__(self, level):
		self.level = level
		self.Position = ( 600, 300 )
		self.Velocity = ( 0.0, 0.0 )
		self.Target = ( 600, 300 )
		self.Waypoint = None
		self.Wander = ( 0.0, 0.0 )
		self.Rotation = 0.0
		self.spriteName = "./images/PlayerTanks.png"
		self.size = (57, 72 )
		self.origin = (0.5, 0.5)
		self.spriteID = AIE.CreateSprite( self.spriteName, self.size[0], self.size[1], self.origin[0], self.origin[1],
                                          71.0/459.0, 1.0 - 72.0/158.0, 128/459.0, 1.0 , 0xff, 0xff, 0xff, 0xff )
		print "spriteID", self.spriteID
		level.register( self, TankEntity.recalculateRoute )
		self.turret = Turret(self)

	def recalculateRoute( self ):
		self.Waypoint = self.Target

	def isWithin( self, xPos, yPos, radius ):
		if( xPos == self.Position[0] and yPos == self.Position[1] ):
			return True
		squaredDistance = ( self.Position[0] - xPos )**2 + ( self.Position[1] - yPos )**2
		if( squaredDistance < radius**2 ):
			return True
		return False

	def slowWithin( self, xPos, yPos, radius, breakPower ):
		if( xPos == self.Position[0] and yPos == self.Position[1] ):
			return ( -self.Velocity[0] * breakPower, -self.Velocity[1] * breakPower )
		if( not self.isWithin( xPos, yPos, radius ) ):
			return ( 0.0, 0.0 )
		squaredDistance = ( self.Position[0] - xPos )**2 + ( self.Position[1] - yPos )**2
		breakStrength = ( 1 - squaredDistance/radius**2 ) * breakPower
		return ( -self.Velocity[0] * breakStrength, -self.Velocity[1] * breakStrength )

	def seek( self, xPos, yPos, turnPower ):
		displacement = ( self.Position[0] - xPos, self.Position[1] - yPos )
		squaredDistance = displacement[0]**2 + displacement[1]**2
		if( squaredDistance <= 0.0 ):
			return ( 0.0, 0.0 )
		distance = math.sqrt( squaredDistance )
		speed = math.sqrt( self.Velocity[0]**2 + self.Velocity[1]**2 )
		return ( -turnPower * ( displacement[0]*speed/distance + self.Velocity[0] ),
                 -turnPower * ( displacement[1]*speed/distance + self.Velocity[1] ) )

	def accelerateTo( self, speed, acceleration, cruiseSpeedRange ):

        # if already at desired speed, no more acceleration is needed
		speedSquared = self.Velocity[0]**2 + self.Velocity[1]**2
		if( speedSquared == speed**2 ):
			return ( 0.0, 0.0 )

        # calculate acceleration direction
		currentSpeed = math.sqrt( speedSquared )
		direction = ( 0.0, 0.0 )
		if( currentSpeed <= 0.0 ):
			direction = ( math.cos( self.Rotation ), math.sin( self.Rotation ) )
		else:
			direction = ( self.Velocity[0] / currentSpeed,
                          self.Velocity[1] / currentSpeed )

        # calculate acceleration magnitude
		cruiseMinSpeed = speed - min( speed, cruiseSpeedRange )
		cruiseMaxSpeed = speed + cruiseSpeedRange
		magnitude = acceleration if ( currentSpeed < speed ) else -acceleration
		if( cruiseMinSpeed < currentSpeed < cruiseMaxSpeed ):
			speedThreshold = ( cruiseMinSpeed if ( currentSpeed < speed ) else cruiseMaxSpeed )
			magnitude *= ( currentSpeed - speed ) / ( speedThreshold - speed )

        # return result
		return ( direction[0] * magnitude, direction[1] * magnitude )

	def accelerateAndSeek( self, xPos, yPos, turnPower, speed, acceleration, cruiseSpeedRange ):
		seek = self.seek( xPos, yPos, turnPower )
		accel = self.accelerateTo( speed, acceleration, cruiseSpeedRange )
		return ( seek[0] + accel[0], seek[1] + accel[1] )

	def arriveWithin( self, xPos, yPos, breakRadius, breakPower, turnPower, speed, acceleration, cruiseSpeedRange ):
		if( self.isWithin( xPos, yPos, breakRadius ) ):
			seek = self.seek( xPos, yPos, turnPower )
			slow = self.slowWithin( xPos, yPos, breakRadius, breakPower )
			return ( seek[0] + slow[0], seek[1] + slow[1] )
		return self.accelerateAndSeek( xPos, yPos, turnPower, speed, acceleration, cruiseSpeedRange )

	def avoidCollisions( self, turnDistance, turnPower, breakPower, fDeltaTime ):

		# if inside an obstacle, it's far too late.  Just keep going.
		xGrid, yGrid = self.level.toGrid( self.Position[0], self.Position[1] )
		if( self.level.obstacleAt( xGrid, yGrid ) ):
			return ( 0.0, 0.0 )

        # check to see if there are any obstacles ahead given current direction
		speed = math.sqrt( self.Velocity[0]**2 + self.Velocity[1]**2 )
		direction = ( ( math.cos( self.Rotation ), math.sin( self.Rotation ) ) if ( 0.0 == speed )
                      else ( self.Velocity[0] / speed, self.Velocity[1] / speed ) )
		xDir = 0 if ( 0.0 == direction[0] ) else -1 if ( 0.0 > direction[0] ) else 1
		yDir = 0 if ( 0.0 == direction[1] ) else -1 if ( 0.0 > direction[1] ) else 1
		obstacles = []
		if( 0 == xDir ):
			if( self.level.obstacleAt( xGrid - 1, yGrid ) ):
				obstacles.append( ( -1, 0 ) )
			if( self.level.obstacleAt( xGrid - 1, yGrid + yDir ) ):
				obstacles.append( ( -1, yDir ) )
			if( self.level.obstacleAt( xGrid, yGrid + yDir ) ):
				obstacles.append( ( 0, yDir ) )
			if( self.level.obstacleAt( xGrid + 1, yGrid + yDir ) ):
				obstacles.append( ( 1, yDir ) )
			if( self.level.obstacleAt( xGrid + 1, yGrid ) ):
				obstacles.append( ( 1, 0 ) )
		elif( 0 == yDir ):
			if( self.level.obstacleAt( xGrid, yGrid - 1 ) ):
				obstacles.append( ( 0, -1 ) )
			if( self.level.obstacleAt( xGrid + xDir, yGrid - 1 ) ):
				obstacles.append( ( xDir, -1 ) )
			if( self.level.obstacleAt( xGrid + xDir, yGrid ) ):
				obstacles.append( ( xDir, 0 ) )
			if( self.level.obstacleAt( xGrid + xDir, yGrid + 1 ) ):
				obstacles.append( ( xDir, 1 ) )
			if( self.level.obstacleAt( xGrid, yGrid + 1 ) ):
				obstacles.append( ( 0, 1 ) )
		else:
			if( self.level.obstacleAt( xGrid - xDir, yGrid + yDir ) ):
				obstacles.append( ( -xDir, yDir ) )
			if( self.level.obstacleAt( xGrid, yGrid + yDir ) ):
				obstacles.append( ( 0, yDir ) )
			if( self.level.obstacleAt( xGrid + xDir, yGrid + yDir ) ):
				obstacles.append( ( xDir, yDir ) )
			if( self.level.obstacleAt( xGrid + xDir, yGrid ) ):
				obstacles.append( ( xDir, 0 ) )
			if( self.level.obstacleAt( xGrid + xDir, yGrid - yDir ) ):
				obstacles.append( ( xDir, -yDir ) )

        # if there are no obstacles in the way, just keep going
		if( 0 == len( obstacles ) ):
			return ( 0.0, 0.0 )

		# "whiskers" should intersect with any obstacle edges close enough to worry about colliding
		whiskerLength = self.size[1] + turnDistance + speed*fDeltaTime
		leftWhisker = ( self.Position[0] - ( direction[0]*self.size[1] + direction[1]*self.size[0] )/2,
                        self.Position[1] + ( direction[0]*self.size[0] - direction[1]*self.size[1] )/2 )
		rightWhisker = ( self.Position[0] - ( direction[0]*self.size[1] - direction[1]*self.size[0] )/2,
                         self.Position[1] - ( direction[0]*self.size[0] + direction[1]*self.size[1] )/2 )
		leftWhisker = ( leftWhisker[0], leftWhisker[1],
                        leftWhisker[0] + direction[0]*whiskerLength,
                        leftWhisker[1] + direction[1]*whiskerLength )
		rightWhisker = ( rightWhisker[0], rightWhisker[1],
                         rightWhisker[0] + direction[0]*whiskerLength,
                         rightWhisker[1] + direction[1]*whiskerLength )
        
		leftDistance = -1
		rightDistance = -1
		minDistance = -1

        # loop through obstacles to find closest one for each whisker
		for obstacle in obstacles:

			# get distance from each whisker
			fLeft = self.level.distanceToObstacle( xGrid + obstacle[0], yGrid + obstacle[1],
                                                   leftWhisker[0], leftWhisker[1],
                                                   direction[0], direction[1] )
			fRight = self.level.distanceToObstacle( xGrid + obstacle[0], yGrid + obstacle[1],
                                                    rightWhisker[0], rightWhisker[1],
                                                    direction[0], direction[1] )
			fCenter = self.level.distanceToObstacle( xGrid + obstacle[0], yGrid + obstacle[1],
                                                     ( leftWhisker[0] + rightWhisker[0] ) / 2,
                                                     ( leftWhisker[1] + rightWhisker[1] ) / 2,
                                                     direction[0], direction[1] )

            # if the shortest distance is close enough to prompt turning,
			fMin = ( -1 if ( -1 == fLeft and -1 == fRight and -1 == fCenter )
                     else fLeft if ( -1 == fRight and -1 == fCenter )
                     else fRight if ( -1 == fLeft and -1 == fCenter )
                     else fCenter if ( -1 == fLeft and -1 == fRight )
                     else min( fLeft, fRight ) if ( -1 == fCenter )
                     else min( fLeft, fCenter ) if ( -1 == fRight )
                     else min( fRight, fCenter ) if ( -1 == fLeft )
                     else min( fLeft, fRight, fCenter ) )
			if( -1 != fMin and fMin < whiskerLength ):

                # make sure at least one of the left and right whiskers registers the collision
				if( -1 != fCenter and -1 == fLeft and -1 == fRight ):
					fEndLeft = self.level.distanceToObstacle( xGrid + obstacle[0], yGrid + obstacle[1],
                                                              leftWhisker[2], leftWhisker[3],
                                                              direction[1], -direction[0] )
					fEndRight = self.level.distanceToObstacle( xGrid + obstacle[0], yGrid + obstacle[1],
                                                               rightWhisker[2], rightWhisker[3],
                                                               -direction[1], direction[0] )
					if( fEndLeft < fEndRight ):
						fLeft = fCenter
					else:
						fRight = fCenter

				# update closest collision distances
				minDistance = min( fMin, minDistance ) if ( -1 != minDistance ) else fMin
				leftDistance = ( min( fLeft, leftDistance ) if ( -1 != leftDistance )
                                 else fLeft if ( -1 != fLeft ) else leftDistance )
				rightDistance = ( min( fRight, rightDistance ) if ( -1 != rightDistance )
                                  else fRight if ( -1 != fRight ) else rightDistance )

            # end of checking obstacles

        # if neither whisker registered a collision, return no force
		if( -1 == leftDistance and -1 == rightDistance ):
			return ( 0.0, 0.0 )

		# calculate turn force
		force = speed * turnPower
		breakForce = 0
		if( minDistance >= self.size[1] ):
			breakForce = ( ( minDistance - self.size[1] )**2/
                           ( whiskerLength - self.size[1] )**2 - 1 ) * speed * breakPower
		if( ( leftDistance == rightDistance and bool(random.getrandbits(1)) ) or
            -1 == rightDistance or ( -1 != leftDistance and leftDistance < rightDistance ) ):
			force *= -1
		return ( direction[0]*breakForce - direction[1]*force,
                 direction[1]*breakForce + direction[0]*force )

	def wander( self, wanderPower, wanderOffset, wanderRadius, changeRate, fDeltaTime ):
		deltaWander = ( random.random() * wanderRadius * fDeltaTime * changeRate *
                        ( 1 if bool(random.getrandbits(1)) else -1 ),
                        random.random() * wanderRadius * fDeltaTime * changeRate *
                        ( 1 if bool(random.getrandbits(1)) else -1 ) )
		print "Wander: ", self.Wander, ", deltaWander: ", deltaWander
		wander = ( self.Wander[0] + deltaWander[0], self.Wander[1] + deltaWander[1] )
		correction = math.sqrt( wanderRadius**2 / ( wander[0]**2 + wander[1]**2 ) )
		wander = ( wander[0] * correction, wander[1] * correction )
		self.Wander = wander
		wander = ( wander[0] + wanderOffset, wander[1] )
		speed = math.sqrt( ( self.Velocity[0]**2 + self.Velocity[1]**2 ) / ( wander[0]**2 + wander[1]**2 ) )
		c = math.cos( self.Rotation )
		s = math.sin( self.Rotation )
		return ( ( ( wander[0]*c - wander[1]*s )*speed - self.Velocity[0] ) * wanderPower,
                 ( ( wander[0]*s + wander[1]*c )*speed - self.Velocity[1] ) * wanderPower )

	def update(self, fDeltaTime ):

        # recalculate route if right mouse button is clicked
		mouseX, mouseY = AIE.GetMouseLocation()
		if( AIE.GetMouseButton(1) ):
			self.Target = ( mouseX, mouseY )
			self.recalculateRoute()

        # calculate acceleration
		accelerations = []
		if( None == self.Waypoint or
            not self.level.lineOfSight( self.Position[0], self.Position[1],
                                        self.Waypoint[0], self.Waypoint[1],
                                        True, False ) ):
			accelerations.append( self.accelerateTo( 150, 150, 10 ) )
			accelerations.append( self.wander( 150, 20, 10, 10, fDeltaTime ) )
		else:
			accelerations.append( self.arriveWithin( self.Waypoint[0], self.Waypoint[1], 20, 20, 10, 250, 250, 10 ) )
		accelerations.append( self.avoidCollisions( 50, 10, 20, fDeltaTime ) )
		acceleration = ( 0.0, 0.0 )
		for accel in accelerations:
			acceleration = ( acceleration[0] + accel[0], acceleration[1] + accel[1] )

        # calculate position, velocity, and rotation
		self.Position = ( self.Position[0] + self.Velocity[0]*fDeltaTime + acceleration[0]*fDeltaTime**2/2,
                          self.Position[1] + self.Velocity[1]*fDeltaTime + acceleration[1]*fDeltaTime**2/2 )
		self.Position = ( math.fmod( self.Position[0], self.level.screenSize[0] ),
                          math.fmod( self.Position[1], self.level.screenSize[1] ) )
		self.Position = ( self.Position[0] + self.level.screenSize[0] if ( self.Position[0] < 0.0 ) else self.Position[0],
                          self.Position[1] + self.level.screenSize[1] if ( self.Position[1] < 0.0 ) else self.Position[1] )
		self.Velocity = ( self.Velocity[0] + acceleration[0] * fDeltaTime,
                          self.Velocity[1] + acceleration[1] * fDeltaTime )
		if( self.Velocity[0] != 0.0 or self.Velocity[1] != 0.0 ):
			self.Rotation = math.atan2( -self.Velocity[1], self.Velocity[0] )

        # move OpenGL sprite and turret sprite
		AIE.PositionSprite( self.spriteID, math.degrees( self.Rotation - ( math.pi / 2 ) ), self.Position[0], self.Position[1] )
		self.turret.update(fDeltaTime)
	
	def draw(self):
		
		AIE.DrawSprite( self.spriteID )
		self.turret.draw()
		
	def getImageName(self):
		return self.imageName
		
	def getState(self):
		return self.state
	
	def getSpriteID(self):
		return self.spriteID
		
	def setSpriteID(self, a_spriteID):
		self.spriteID = a_spriteID
	
	def getPosition(self):
		return self.Position

	def cleanUp(self):
		self.turret.cleanUp()
		AIE.DestroySprite( self.spriteID )
		
#Turret
#    This is an Entity Object that has an owner, it is up to you to implement inheritance (BaseEntity->Turret) 
#    The Turret's position is based on the location of it's owner, if it's owner (in this scenario a Tank) is moveable
#    The turret will move with it's base/owner

class Turret:
	
	def __init__(self, owner):
		self.owner = owner
		self.Position = ( 0, 0 )
		self.Rotation = 0
		self.spriteName = "./images/PlayerTanks.png"
		self.size = (29, 60 )
		self.origin = (0.55, 0.75)
		self.spriteID = AIE.CreateSprite( self.spriteName, self.size[0], self.size[1], self.origin[0], self.origin[1],
                                          129.0/459.0, 1.0 - 61.0/158.0, 157.0/459.0, 1.0 , 0xff, 0xff, 0xff, 0xff )
		print "spriteID", self.spriteID
	
	def update(self, fDeltaTime):
		turretLocation = self.owner.getPosition()
		mouseX, mouseY = AIE.GetMouseLocation()
		rotation = math.atan2( -mouseY + turretLocation[1], mouseX - turretLocation[0] )
		AIE.PositionSprite( self.spriteID, math.degrees( rotation - ( math.pi / 2 ) ), turretLocation[0], turretLocation[1] )
		
	def draw(self):
		AIE.DrawSprite( self.spriteID )
	
	def	cleanUp(self):
		AIE.DestroySprite( self.spriteID )
		
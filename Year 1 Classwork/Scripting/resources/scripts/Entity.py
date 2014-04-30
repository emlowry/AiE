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
		self.Target = None
		self.TargetSize = ( 32, 32 )
		self.SettingTarget = False
		self.RemovingTarget = False
		self.Waypoint = None
		self.Wander = 0.0
		self.WanderTime = 0.0
		self.Rotation = 0.0
		self.spriteName = "./images/PlayerTanks.png"
		self.targetSpriteName = "./images/crate_sideup.png"
		self.size = (57, 72 )
		self.origin = (0.5, 0.5)
		self.spriteID = AIE.CreateSprite( self.spriteName, self.size[0], self.size[1], self.origin[0], self.origin[1],
                                          71.0/459.0, 1.0 - 72.0/158.0, 128/459.0, 1.0 , 0xff, 0xff, 0xff, 0xff )
		self.targetSpriteID = AIE.CreateSprite( self.targetSpriteName, self.TargetSize[0], self.TargetSize[1], 0.5, 0.5,
                                                0.0, 0.0, 1.0, 1.0 , 0xff, 0xff, 0xff, 0xff )
		print "spriteID", self.spriteID, " target spriteID", self.targetSpriteID
		level.register( self, TankEntity.recalculateRoute )
		self.turret = Turret(self)

	def recalculateRoute( self, level = None ):
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

	def mostThreateningObstacle( self, whiskerExtension, direction, obstacles ):
		minDistance = -1
		mostThreatening = None

		whiskerLength = self.size[1] + whiskerExtension
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
        
        # loop through obstacles to find closest one for each whisker
		for obstacle in obstacles:

			# get distance from each whisker
			fLeft = self.level.distanceToObstacle( obstacle[0], obstacle[1],
                                                   leftWhisker[0], leftWhisker[1],
                                                   direction[0], direction[1] )
			fRight = self.level.distanceToObstacle( obstacle[0], obstacle[1],
                                                    rightWhisker[0], rightWhisker[1],
                                                    direction[0], direction[1] )
			fCenter = self.level.distanceToObstacle( obstacle[0], obstacle[1],
                                                     ( leftWhisker[0] + rightWhisker[0] ) / 2,
                                                     ( leftWhisker[1] + rightWhisker[1] ) / 2,
                                                     direction[0], direction[1] )

            # if the shortest distance is close enough to prompt turning, update closest collision distances
			fMin = ( -1 if ( -1 == fLeft and -1 == fRight and -1 == fCenter )
                     else fLeft if ( -1 == fRight and -1 == fCenter )
                     else fRight if ( -1 == fLeft and -1 == fCenter )
                     else fCenter if ( -1 == fLeft and -1 == fRight )
                     else min( fLeft, fRight ) if ( -1 == fCenter )
                     else min( fLeft, fCenter ) if ( -1 == fRight )
                     else min( fRight, fCenter ) if ( -1 == fLeft )
                     else min( fLeft, fRight, fCenter ) )
			if( -1 != fMin and fMin < whiskerLength and ( -1 == minDistance or fMin < minDistance ) ):
				minDistance = fMin
				mostThreatening = obstacle

            # end of checking obstacles

		return mostThreatening

	def turnDirection( self, obstacle, whiskerLength, direction ):
		corners = self.level.toCorners( obstacle[0], obstacle[1] )
		center = ( ( corners[0] + corners[2] ) / 2, ( corners[1] + corners[3] ) / 2 )
		whiskerEnd = ( self.Position[0] + direction[0]*( self.size[1]/2 + whiskerLength ),
                       self.Position[1] + direction[1]*( self.size[1]/2 + whiskerLength ) )
		turn = ( whiskerEnd[0] - center[0], whiskerEnd[1] - center[1] )
		correction = math.sqrt( turn[0]**2 + turn[1]**2 )
		return ( turn[0] * correction, turn[1] * correction )

	def avoidCollisions( self, turnDistance, turnPower, fDeltaTime = 0.0 ):

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
		obstacles = self.level.getObstacles( xGrid, yGrid, xDir, yDir, True )

        # if there are no obstacles in the way, just keep going
		if( 0 == len( obstacles ) ):
			return ( 0.0, 0.0 )
            
		# get the most threatening obstacle
		mostThreatening = self.mostThreateningObstacle( turnDistance + speed*fDeltaTime, direction, obstacles )

        # if no obstacles threaten collision, return no force
		if( None == mostThreatening ):
			return ( 0.0, 0.0 )

		# calculate turn force
		turnForce = speed * turnPower
		turn = self.turnDirection( mostThreatening, speed*fDeltaTime, direction )
		return ( turn[0] * turnForce, turn[1] * turnForce )

	def wander( self, wanderPower, wanderOffset, wanderRadius, changeRadius, fDeltaTime = 0.0, changeInterval = 0.0 ):
		self.WanderTime += fDeltaTime
		wander = ( math.cos( self.Wander )*wanderRadius, math.sin( self.Wander )*wanderRadius )
		if( 0.0 >= changeInterval or self.WanderTime >= changeInterval ):
			self.WanderTime = math.fmod( self.WanderTime, changeInterval )
			deltaWander = random.uniform( 0, 2*math.pi )
			wander = ( wander[0] + math.cos( deltaWander )*changeRadius,
                       wander[1] + math.sin( deltaWander )*changeRadius )
			self.Wander = math.atan2( wander[1], wander[0] )
			correction = wanderRadius / math.sqrt( wander[0]**2 + wander[1]**2 )
			wander = ( wander[0]*correction, wander[1]*correction )
		wander = ( wander[0] + wanderOffset, wander[1] )
		speed = math.sqrt( ( self.Velocity[0]**2 + self.Velocity[1]**2 ) / ( wander[0]**2 + wander[1]**2 ) )
		c = math.cos( self.Rotation )
		s = math.sin( self.Rotation )
		return ( ( ( wander[0]*c - wander[1]*s )*speed - self.Velocity[0] ) * wanderPower,
                 ( ( wander[0]*s + wander[1]*c )*speed - self.Velocity[1] ) * wanderPower )

	def handleMouseInput( self, fDeltaTime ):
		mouseX, mouseY = AIE.GetMouseLocation()
		if( AIE.GetMouseButton(1) ):
			if( not self.SettingTarget and None != self.Target and
                -self.TargetSize[0]/2 <= self.Target[0] - mouseX <= self.TargetSize[0]/2 and
                -self.TargetSize[1]/2 <= self.Target[1] - mouseY <= self.TargetSize[1]/2 ):
				print "Removing target"
				self.Target = None
				self.recalculateRoute()
				self.RemovingTarget = True
			elif( not self.RemovingTarget ):
				self.Target = ( mouseX, mouseY )
				print "Setting target at ", self.Target
				AIE.MoveSprite( self.targetSpriteID, self.Target[0], self.Target[1] )
				self.recalculateRoute()
				self.SettingTarget = True
		elif( self.SettingTarget or self.RemovingTarget ):
			self.SettingTarget = False
			self.RemovingTarget = False

	def calculateForce( self, fDeltaTime ):
		forces = [ self.avoidCollisions( 50, 1, fDeltaTime ) ]
		if( None == self.Waypoint or
            not self.level.lineOfSight( self.Position[0], self.Position[1],
                                        self.Waypoint[0], self.Waypoint[1],
                                        True, False ) ):
			forces.append( self.accelerateTo( 150, 150, 10 ) )
			forces.append( self.wander( 10, 3, 1, 1, fDeltaTime, 0.25 ) )
		else:
			forces.append( self.seek( self.Waypoint[0], self.Waypoint[1], 10 ) )
			if( self.Waypoint != self.Target or not self.isWithin( self.Waypoint[0], self.Waypoint[1], 40 ) ):
				forces.append( self.accelerateTo( 250, 250, 10 ) )
			if( self.Waypoint == self.Target and self.isWithin( self.Waypoint[0], self.Waypoint[1], 80 ) ):
				forces.append( self.slowWithin( self.Waypoint[0], self.Waypoint[1], 80, 20 ) )
		totalForce = ( 0.0, 0.0 )
		for force in forces:
			totalForce = ( totalForce[0] + force[0], totalForce[1] + force[1] )
		return totalForce

	def applyForce( self, force, fDeltaTime ):
		acceleration = force
		self.Position = ( ( self.Position[0] + self.Velocity[0]*fDeltaTime +
                            acceleration[0]*fDeltaTime**2/2 ) % self.level.screenSize[0],
                          ( self.Position[1] + self.Velocity[1]*fDeltaTime +
                            acceleration[1]*fDeltaTime**2/2 ) % self.level.screenSize[1] )
		self.Velocity = ( self.Velocity[0] + acceleration[0] * fDeltaTime,
                          self.Velocity[1] + acceleration[1] * fDeltaTime )
		if( self.Velocity[0] != 0.0 or self.Velocity[1] != 0.0 ):
			self.Rotation = math.atan2( self.Velocity[1], self.Velocity[0] )

	def update(self, fDeltaTime ):

        # recalculate route if right mouse button is clicked
		self.handleMouseInput( fDeltaTime )

        # calculate forces on object
		force = self.calculateForce( fDeltaTime )

        # calculate position, velocity, and rotation
		self.applyForce( force, fDeltaTime )

        # remove target if arrived at
		if( None != self.Target and self.Waypoint == self.Target and self.isWithin( self.Waypoint[0], self.Waypoint[1], 40 ) ):
			self.Target = None
			self.recalculateRoute()

        # move OpenGL sprite and turret sprite
		AIE.PositionSprite( self.spriteID, math.degrees( -self.Rotation - ( math.pi / 2 ) ), self.Position[0], self.Position[1] )
		self.turret.update(fDeltaTime)
	
	def draw(self):
		if( None != self.Target ):
		    AIE.DrawSprite( self.targetSpriteID )
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
		rotation = math.atan2( mouseY - turretLocation[1], mouseX - turretLocation[0] )
		AIE.PositionSprite( self.spriteID, math.degrees( -rotation - ( math.pi / 2 ) ), turretLocation[0], turretLocation[1] )
		
	def draw(self):
		AIE.DrawSprite( self.spriteID )
	
	def	cleanUp(self):
		AIE.DestroySprite( self.spriteID )
		